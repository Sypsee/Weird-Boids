#include "headers/Render.h"
#include <iostream>

Render::Render(SDL_Window *window)
    :renderer(NULL)
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
    {
        std::cout << "Failed to create renderer, error : " << SDL_GetError() << std::endl;
    }
}

SDL_Texture* Render::loadTexture(const char* file_path)
{
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(renderer, file_path);

    if (texture == NULL)
    {
        std::cout << "Failed to load texture, error : " << SDL_GetError() << std::endl;
    }

    return texture;
}

void Render::renderTexture(SDL_Texture *texture, SDL_Rect *rect, SDL_Rect *rectDst)
{
    SDL_RenderCopy(renderer, texture, rect, rectDst);
}

void Render::clear()
{
    SDL_RenderClear(renderer);
}

void Render::display()
{
    SDL_RenderPresent(renderer);
}

SDL_Renderer *Render::get_Renderer()
{
    return renderer;
}

void Render::cleanUp()
{
    SDL_DestroyRenderer(renderer);
}