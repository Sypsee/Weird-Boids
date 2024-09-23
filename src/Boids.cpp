#include "Boids.h"

// std
#include <iostream>

Boids::Boids(int numberOfBoids)
    :numberOfBoids(numberOfBoids)
{
    Reset(numberOfBoids);
}

Boids::~Boids()
{
    m_Boids.clear();
}

void Boids::Reset(int numberOfBoids)
{
    m_Boids.clear();

    m_Boids.reserve(numberOfBoids);
    m_BoidObjects.resize(Rect{{0.f, 0.f}, {800.f, 600.f}});

    int y = 0;
    int x = -numberOfBoids/2;
    for (int i = 0; i < numberOfBoids; i++)
    {
        Boid boid{
            (uint16_t)i,  // ID
            Vec2{(float)x, (float)y},   // Pos
            Vec2(rand() % (3 - (-3) + 1) + (-3), rand() % (3 - 0 + 1) + (-3)),   // Move Dir
            static_cast<uint8_t>(((rand())) % 156 + 100), // r
            static_cast<uint8_t>(((rand())) % 156 + 100), // g
            static_cast<uint8_t>(((rand())) % 156 + 100)};// b
        
        m_Boids.push_back(boid);
        m_BoidObjects.insert(boid, Rect{boid.pos, {bRect.w, bRect.h}});

        x += 20;

        if (i % 69 == 0)
        {
            y+=20;
            x = -numberOfBoids/2;
        }
    }
}

void Boids::Update()
{
    for (auto boidIt = m_BoidObjects.begin(); boidIt != m_BoidObjects.end(); boidIt++)
    {
        auto &boid = boidIt->item;

        // Update direction
        Vec2 force = {0.f, 0.f};
        Vec2 dir = {0.f,0.f};
        Vec2 sumAdjacentPos{0.f, 0.f};
        Vec2 sumAdjacentMoveDir{0.f, 0.f};
        int adjacentBoidCount = 0;

        for (auto &adjacentBoid : m_BoidObjects.search(Rect{boid.pos, {20.f, 20.f}}))
        {
            if (boid.id == adjacentBoid->item.id || (adjacentBoid->item.pos - boid.pos).magnitude() > maxNegihbourRadius) continue;
            
            Vec2 diff = (adjacentBoid->item.pos - boid.pos);
            const float dist = diff.magnitude();
            dir -= (diff / (dist * dist));

            if (boid.velocity.dot(adjacentBoid->item.velocity) < maxViewAngle) continue;

            adjacentBoidCount++;
            sumAdjacentPos += adjacentBoid->item.pos;
            sumAdjacentMoveDir += adjacentBoid->item.velocity;

            adjacentBoid->item.r = boid.r;
            adjacentBoid->item.g = boid.g;
            adjacentBoid->item.b = boid.b;
        }

        // for (Boid &adjacentBoid : m_Boids)
        // {
        //     if (boid.id == adjacentBoid.id || (adjacentBoid.pos - boid.pos).magnitude() > maxNegihbourRadius) continue;
            
        //     Vec2 diff = (adjacentBoid.pos - boid.pos);
        //     const float dist = diff.magnitude();
        //     dir -= (diff / (dist * dist));

        //     if (boid.velocity.dot(adjacentBoid.velocity) < maxViewAngle) continue;

        //     adjacentBoidCount++;
        //     sumAdjacentPos += adjacentBoid.pos;
        //     sumAdjacentMoveDir += adjacentBoid.velocity;

        //     adjacentBoid.r = boid.r;
        //     adjacentBoid.g = boid.g;
        //     adjacentBoid.b = boid.b;
        // }

        if (adjacentBoidCount > 0)
        {            
            Vec2 avgPos = sumAdjacentPos / adjacentBoidCount;
            Vec2 avgMoveDir = sumAdjacentMoveDir / adjacentBoidCount;

            force += (avgPos - boid.pos) * cohesionFactor;           // cohesion
            force += (avgMoveDir - boid.velocity) * alignmentFactor; // alignment
        }

        force += dir * seprationFactor;                              // sepration

        // Update pos & vel
        boid.pos += boid.velocity;
        boid.velocity += force;

        m_BoidObjects.relocate(boidIt, {boid.pos, {bRect.w, bRect.h}});

        // Limit Max Speed
        if (boid.velocity.magnitude() > maxSpeed)
        {
            boid.velocity = boid.velocity.normalized() * maxSpeed;
        }

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        mouseX -= 400;  // Convert to World Space
        mouseY -= 300;  // Convert to World Space

        Vec2 mousePos = {(float)mouseX, (float)mouseY};
        Vec2 repulsion = (boid.pos - mousePos);
        if (repulsion.magnitude() < mouseRepelRadius && mousePos.x < 400 && mousePos.y < 250)
        {
            const float repelDist = repulsion.magnitude();
            if (repelDist > 0)
            {
                repulsion = repulsion.normalized();
                repulsion = repulsion / (repelDist);
                repulsion = (repulsion) * mouseRepelForce;

                boid.velocity += repulsion;
            }
        }

        // Bound checks
        if (boid.pos.x > 400 || boid.pos.x < -400)
        {
            boid.pos.x = -boid.pos.x;
        }
        if (boid.pos.y > 300 || boid.pos.y < -300)
        {
            boid.pos.y = -boid.pos.y;
        }
    }
}

void Boids::Draw(SDL_Renderer *renderer)
{
    for (Boid &boid : m_Boids)
    {
        bRect.x = boid.pos.x + 400;
        bRect.y = boid.pos.y + 300;

        SDL_SetRenderDrawColor(renderer, boid.r, boid.g, boid.b, 255);
        SDL_RenderFillRect(renderer, &bRect);
    }
}