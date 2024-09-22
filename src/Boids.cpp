#include "Boids.h"

// std
#include <iostream>

Boids::Boids(int numberOfBoids)
    :numberOfBoids(numberOfBoids)
{
    m_Boids.reserve(numberOfBoids);
    int y = 0;
    int x = -numberOfBoids/2;
    for (int i = 0; i < numberOfBoids; i++)
    {
        Boid boid{
            i,  // ID
            Vec2{x, y},   // Pos
            Vec2(rand() % (1 - 0 + 1) + 0, rand() % (1 - 0 + 1) + 0),   // Move Dir
            static_cast<uint8_t>(((rand() * 10) + 10) % 256), // r
            static_cast<uint8_t>(((rand() * 10) + 10) % 256), // g
            static_cast<uint8_t>(((rand() * 10) + 10) % 256)};// b

        m_Boids.push_back(boid);

        x += 5;

        if (i % 10 == 0)
        {
            y+=5;
            x = -numberOfBoids/2;
        }
    }
}

Boids::~Boids()
{
    m_Boids.clear();
}

void Boids::Reset(int numberOfBoids)
{
    m_Boids.clear();

    m_Boids.reserve(numberOfBoids);
    int y = 0;
    int x = -numberOfBoids/2;
    for (int i = 0; i < numberOfBoids; i++)
    {
        Boid boid{
            i,  // ID
            Vec2{x, y},   // Pos
            Vec2(rand() % (1 - 0 + 1) + 0, rand() % (1 - 0 + 1) + 0),   // Move Dir
            static_cast<uint8_t>(((rand() * 10) + 10) % 256), // r
            static_cast<uint8_t>(((rand() * 10) + 10) % 256), // g
            static_cast<uint8_t>(((rand() * 10) + 10) % 256)};// b
        
        m_Boids.push_back(boid);

        x += 5;

        if (i % 10 == 0)
        {
            y+=5;
            x = -numberOfBoids/2;
        }
    }
}

void Boids::Update()
{
    for (Boid &boid : m_Boids)
    {
        // Update direction
        Vec2 force = {0.f, 0.f};
        Vec2 dir = {0.f,0.f};
        Vec2 sumAdjacentPos{0.f, 0.f};
        Vec2 sumAdjacentMoveDir{0.f, 0.f};
        int adjacentBoidCount = 0;

        for (Boid &adjacentBoid : m_Boids)
        {
            if (boid.id == adjacentBoid.id || (adjacentBoid.pos - boid.pos).magnitude() > maxNegihbourRadius
                || boid.moveDir.dot(adjacentBoid.moveDir) < maxViewAngle) continue;

            adjacentBoidCount++;
            sumAdjacentPos += adjacentBoid.pos;
            sumAdjacentMoveDir += adjacentBoid.moveDir;

            Vec2 diff = (adjacentBoid.pos - boid.pos);
            const float dist = diff.magnitude();
            dir -= (diff / (dist * dist));
        }

        if (adjacentBoidCount > 0)
        {            
            Vec2 avgPos = sumAdjacentPos / adjacentBoidCount;
            Vec2 avgMoveDir = sumAdjacentMoveDir / adjacentBoidCount;

            force += (avgPos - boid.pos) * cohesionFactor;           // cohesion
            force += (avgMoveDir - boid.moveDir) * alignmentFactor;  // alignment
        }

        force += dir * seprationFactor;                              // sepration

        // Update pos
        boid.pos += boid.moveDir;

        boid.moveDir += force;

        // Limit Max Speed
        if (boid.moveDir.magnitude() > maxSpeed)
        {
            boid.moveDir = boid.moveDir.normalized() * maxSpeed;
        }

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        mouseX -= 400;  // Convert to World Space
        mouseY -= 300;  // Convert to World Space

        Vec2 mousePos = {mouseX, mouseY};
        Vec2 repulsion = (boid.pos - mousePos);
        if (repulsion.magnitude() < mouseRepelRadius && mousePos.x < 400 && mousePos.y < 250)
        {
            const float repelDist = repulsion.magnitude();
            if (repelDist > 0)
            {
                repulsion = repulsion.normalized();
                repulsion = repulsion / (repelDist);
                repulsion = (repulsion) * mouseRepelForce;

                boid.moveDir += repulsion;
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