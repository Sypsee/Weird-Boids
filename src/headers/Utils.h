#include <SDL.h>

struct Vec2
{
    int x, y;
};

class Utils
{
public:
    bool point_in_rect(Vec2 point, SDL_Rect rect);
    bool rect_collision(SDL_Rect rectA, SDL_Rect rectB);
    int approach(int current, int target, int increase);
};