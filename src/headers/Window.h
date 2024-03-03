#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Window
{
public:
    Window(const char* name, int w, int h);
    SDL_Window *get_Window();
    void cleanUp();

private:
    SDL_Window *window;
};