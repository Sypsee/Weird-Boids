#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Render
{
public:
    Render(SDL_Window *window);
    SDL_Texture* loadTexture(const char* file_path);
    void renderTexture(SDL_Texture *texture, SDL_Rect *rect, SDL_Rect *rectDst);
    SDL_Renderer *get_Renderer();
    void display();
    void clear();
    void cleanUp();

private:
    SDL_Renderer *renderer;
};