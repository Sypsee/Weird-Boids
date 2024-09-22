#pragma once

#include <SDL.h>
#include <vector>

#include "math.h"

struct Boid
{
    uint16_t id;
    Vec2 pos;
    Vec2 moveDir;
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

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
    float maxViewAngle = -0.15f;
    float mouseRepelForce = 2.f;
    float mouseRepelRadius = 50.f;

    int numberOfBoids = 0;

private:
    std::vector<Boid> m_Boids;
    SDL_Rect bRect{
        0, 0, 5, 5
    };
};