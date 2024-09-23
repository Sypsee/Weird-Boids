#pragma once

#include <SDL.h>

#include "Boids.h"

class Renderer
{
public:
    Renderer(SDL_Window* window);
    ~Renderer();

    void Draw();

private:
    SDL_Renderer *m_Renderer;

    uint64_t currentFrame = 0, lastFrame = 0;
    double deltaTime;

    // BOIDS
    Boids m_Boids{800};
};