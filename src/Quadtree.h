#pragma once

#include "Boid.h"

#include <vector>
#include <array>
#include <list>
#include <memory>
#include <iterator>

#define MAX_DEPTH 8

template <typename T>
struct QuadTreeItemLocation
{
    typename std::list<std::pair<Rect, T>> *container;
    typename std::list<std::pair<Rect, T>>::iterator iterator;
};

template <typename objType>
class QuadTree
{
public:
    QuadTree(const Rect &size = {{0.0f, 0.0f}, {20.f, 20.f}}, const size_t depth = 0)
    {
        m_Depth = depth;
        resize(size);
    }

    void resize(const Rect &rect)
    {
        clear();
        m_Rect = rect;
        Vec2 ChildSize = m_Rect.size / 2.f;

        m_rChilds =
        {
            Rect(m_Rect.pos, ChildSize),
            Rect({m_Rect.pos.x + ChildSize.x, m_Rect.pos.y}, ChildSize),
            Rect({m_Rect.pos.x, m_Rect.pos.y + ChildSize.y}, ChildSize),
            Rect(m_Rect.pos + ChildSize, ChildSize)
        };
    }

    void clear()
    {
        m_pItems.clear();
        for (int i = 0; i < 4; i++)
        {
            if (m_pChilds[i])
                m_pChilds[i]->clear();
            m_pChilds[i].reset();
        }
    }

    size_t size() const
    {
        size_t count = m_pItems.size();
        for (int i = 0; i < 4; i++)
            if (m_pChilds[i]) count += m_pChilds[i]->size();

        return count;
    }

    QuadTreeItemLocation<objType> insert(const objType &item, const Rect &itemSize)
    {
        for (int i=0; i<4; i++)
        {
            if (m_rChilds[i].contains(itemSize))
            {
                if (m_Depth + 1 < MAX_DEPTH)
                {
                    if (!m_pChilds[i])
                    {
                        m_pChilds[i] = std::make_shared<QuadTree<objType>>(m_rChilds[i], m_Depth++);
                    }

                    return m_pChilds[i]->insert(item, itemSize);
                }
            }
        }

        m_pItems.push_back({itemSize, item});
        return {&m_pItems, std::prev(m_pItems.end())};
    }

    std::list<objType> search(const Rect &rArea) const
    {
        std::list<objType> listItems;
        search(rArea, listItems);
        return listItems;
    }

    void search(const Rect &rArea, std::list<objType> &listItems) const
    {
        for (const auto& p : m_pItems)
        {
            if (rArea.contains(p.first))
                listItems.push_back(p.second);
        }

        for (int i=0; i<4; i++)
        {
            if (m_pChilds[i])
            {
                if (rArea.contains(m_rChilds[i]))
                    m_pChilds[i]->items(listItems);
                else if (m_rChilds[i].overlaps(rArea))
                    m_pChilds[i]->search(rArea, listItems);
            }
        }
    }

    void items(std::list<objType> &listItems) const
    {
        for (const auto &p : m_pItems)
            listItems.push_back(p.second);

        for (int i=0; i<4; i++)
            if (m_pChilds[i]) m_pChilds[i]->items(listItems);
    }

    const Rect &area()
    {
        return m_Rect;
    }

    bool remove(objType pItem)
    {
        return false;
    }

protected:
    size_t m_Depth = 0;

    Rect m_Rect;

    std::array<Rect, 4> m_rChilds{};
    std::array<std::shared_ptr<QuadTree<objType>>, 4> m_pChilds{};
    
    std::list<std::pair<Rect, objType>> m_pItems;
};

template <typename T>
struct QuadTreeItem
{
    T item;
    QuadTreeItemLocation<typename std::list<QuadTreeItem<T>>::iterator> pItem;
};

template <typename objType>
class QuadTreeContainer
{
	// Using a std::list as we dont want pointers to be invalidated to objects stored in the
	// tree should the contents of the tree change
	using SomeQuadTreeContainer = std::list<QuadTreeItem<objType>>;

protected:
	// The actual container
	SomeQuadTreeContainer m_allItems;

	// Use our StaticQuadTree to store "pointers" instead of objects - this reduces
	// overheads when moving or copying objects 
	QuadTree<typename SomeQuadTreeContainer::iterator> root;

public:
	QuadTreeContainer(const Rect& size = { {0.0f, 0.0f}, { 20.0f, 20.0f } }, const size_t depth = 0) : root(size, depth) {}

	// Sets the spatial coverage area of the quadtree
	// Invalidates tree
	void resize(const Rect& rArea)
	{
		root.resize(rArea);
	}

	// Returns number of items within tree
	size_t size() const
	{
		return m_allItems.size();
	}

	// Returns true if tree is empty
	bool empty() const
	{
		return m_allItems.empty();
	}

	// Removes all items from tree
	void clear()
	{
		root.clear();
		m_allItems.clear();
	}


	// Convenience functions for ranged for loop
	typename SomeQuadTreeContainer::iterator begin()
	{
		return m_allItems.begin();
	}

	typename SomeQuadTreeContainer::iterator end()
	{
		return m_allItems.end();
	}

	typename SomeQuadTreeContainer::const_iterator cbegin()
	{
		return m_allItems.cbegin();
	}

	typename SomeQuadTreeContainer::const_iterator cend()
	{
		return m_allItems.cend();
	}


	// Insert item into tree in specified area
	void insert(const objType& item, const Rect& itemsize)
	{
        QuadTreeItem<objType> newItem;
        newItem.item = item;
        m_allItems.push_back(newItem);

        m_allItems.back().pItem = root.insert(std::prev(m_allItems.end()), itemsize);
	}

	// Returns a std::list of pointers to items within the search area
	std::list<typename SomeQuadTreeContainer::iterator> search(const Rect& rArea) const
	{
		std::list<typename SomeQuadTreeContainer::iterator> listItemPointers;
		root.search(rArea, listItemPointers);
		return listItemPointers;
	}

    void remove(typename SomeQuadTreeContainer::iterator item)
    {
        item->pItem.container->erase(item->pItem.iterator);
        m_allItems.erase(item);
    }

    void relocate(typename SomeQuadTreeContainer::iterator &item, const Rect &itemSize)
    {
        item->pItem.container->erase(item->pItem.iterator);
        item->pItem = root.insert(item, itemSize);
    }
};