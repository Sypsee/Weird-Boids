#include "headers/Utils.h"

bool Utils::point_in_rect(Vec2 point, SDL_Rect rect)
{
    return (point.x >= rect.x &&
            point.x <= rect.x + rect.w &&
            point.y >= rect.y &&
            point.y <= rect.y + rect.h);
}

bool Utils::rect_collision(SDL_Rect rectA, SDL_Rect rectB)
{
    return (rectA.x < rectB.x + rectB.w &&
            rectA.x + rectA.w > rectB.x &&
            rectA.y < rectB.x + rectB.w &&
            rectA.y + rectA.h > rectB.y);
}

int min(float a, float b)
{
    if (a < b)
    {
        return a;
    }

    return b;
}

int Utils::approach(int current, int target, int increase)
{
    if (current < target)
    {
        return min(current + increase, target);
    }
    return min(current - increase, target);
}