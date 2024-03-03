#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Render.h"

class Entity
{
public:
    Entity(SDL_Texture* texture, int w, int h, int x, int y);
    void renderEntity(Render renderer);
    int getX();
    int getY();
    void setY(int y);
    void setX(int x);

private:
    SDL_Texture *texture;
    SDL_Rect entity;
    SDL_Rect entityDst;
};