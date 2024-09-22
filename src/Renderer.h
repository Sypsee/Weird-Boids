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

    // BOIDS
    Boids m_Boids{200};
};