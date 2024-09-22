#include "Application.h"

#include <iostream>
#include <imgui_impl_sdl2.h>

Application::Application(){}

Application::~Application() {}

void Application::run()
{
    while (m_IsRunning)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
            {
                m_IsRunning = false;
                break;
            }
            ImGui_ImplSDL2_ProcessEvent(&e);
        }

        renderer.Draw();

        SDL_Delay(16.67f);
    }
}