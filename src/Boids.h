#pragma once

#include <SDL.h>
#include <vector>

#include "Boid.h"
#include "Quadtree.h"

class Boids
{
public:
    Boids(int numberOfBoids);
    ~Boids();

    void Reset(int numberOfBoids);

    void Update();
    void Draw(SDL_Renderer *renderer);

    float cohesionFactor = 0.015f;
    float alignmentFactor = 1.2f;
    float seprationFactor = 2.15f;
    float maxSpeed = 3.f;
    float maxNegihbourRadius = 10.f;
    float maxViewAngle = 0.f;
    float mouseRepelForce = 2.f;
    float mouseRepelRadius = 50.f;

    int numberOfBoids = 0;

private:
    std::vector<Boid> m_Boids;
    SDL_Rect bRect{
        0, 0, 5, 5
    };

    QuadTreeContainer<Boid> m_BoidObjects;
};