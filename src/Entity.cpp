#include "headers/Entity.h"
#include "headers/Render.h"

Entity::Entity(SDL_Texture* texture, int w, int h, int x, int y)
{
    entity.w = w;
    entity.h = h;
    entity.x=0;
    entity.y=0;
    entityDst.w = h*2;
    entityDst.h = w*2;
    entityDst.x = x;
    entityDst.y = y;

    this->texture = texture;
}

int Entity::getX()
{
    return entityDst.x;
}

int Entity::getY()
{
    return entityDst.y;
}

void Entity::setX(int x)
{
    entityDst.x = x;
}

void Entity::setY(int y)
{
    entityDst.y = y;
}

void Entity::renderEntity(Render renderer)
{
    renderer.renderTexture(texture, &entity, &entityDst);
}