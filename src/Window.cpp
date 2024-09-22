#include "Window.h"

// std
#include <iostream>
#include <stdexcept>

Window::Window(const char* title, const uint16_t width, const uint16_t height)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
    {
        std::cout << SDL_GetError() << "\n";
        throw std::runtime_error("Failed to init SDL!\n");
    }
    m_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    if (m_Window == NULL)
    {
        std::cout << SDL_GetError() << "\n";
        throw std::runtime_error("Failed to create SDL_Window!\n");
    }
}

Window::~Window()
{
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}