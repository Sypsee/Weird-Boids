#pragma once

#include <SDL.h>
#include <cstdint>

class Window
{
public:
    Window(const char* title, const uint16_t width, const uint16_t height);
    ~Window();

    SDL_Window* GetSDLWindow() { return m_Window; }

private:
    SDL_Window *m_Window;
};