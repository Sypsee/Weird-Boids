#pragma once

#define SDL_MAIN_HANDLED
#include "Window.h"
#include "Renderer.h"

class Application
{
public:
    Application();
    ~Application();

    void run();

private:
    Window m_Window{"BOIDS!!!", 800, 600};
    SDL_Event e;
    Renderer renderer{m_Window.GetSDLWindow()};
    bool m_IsRunning = true;
};