#include "headers/Window.h"
#include <iostream>

Window::Window(const char* name, int w, int h)
    :window(NULL)
{
    window = SDL_CreateWindow(
        name,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        w,
        h,
        SDL_RENDERER_ACCELERATED
    );

    if (window == NULL)
    {
        std::cout << "Failed to create window, error : " << SDL_GetError() << std::endl;
    }
}

SDL_Window* Window::get_Window()
{
    return window;
}

void Window::cleanUp()
{
    SDL_DestroyWindow(window);
}