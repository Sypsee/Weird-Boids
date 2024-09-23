#pragma once
#include "math.h"

struct Boid
{
    uint16_t id;
    Vec2 pos;
    Vec2 velocity;
    uint8_t r;
    uint8_t g;
    uint8_t b;
};