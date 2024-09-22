#pragma once

#include <iostream>
#include <cmath>

static float Clamp01(float val)
{
    if (val > 1) val = 1;
    if (val < 0) val = 0;

    return val;
}

struct Vec2
{
    float x, y;

    Vec2() :x(0), y(0) {}
    Vec2(float x, float y) :x(x), y(y) {}
    Vec2(const Vec2& other) :x(other.x), y(other.y) {}

    Vec2 operator+(const Vec2 &other) const
    {
        return Vec2{
            this->x+other.x,
            this->y+other.y
        };
    }

    Vec2 operator+(const float k) const
    {
        return Vec2{
            this->x+k,
            this->y+k
        };
    }

    Vec2 operator-(const Vec2 &other) const
    {
        return Vec2{
            this->x-other.x,
            this->y-other.y
        };
    }

    Vec2 operator+=(const Vec2 &other)
    {
        this->x += other.x;
        this->y += other.y;
    }

    Vec2 operator-=(const Vec2 &other)
    {
        this->x -= other.x;
        this->y -= other.y;
    }

    Vec2 operator*(const float k)
    {
        return Vec2{
            this->x * k,
            this->y * k
        };
    }

    Vec2 operator/(const float k)
    {
        return Vec2{
            this->x / k,
            this->y / k
        };
    }

    float dot(const Vec2 &other)
    {
        return this->x * other.x + this->y * other.y;
    }

    float magnitude()
    {
        return sqrt((this->x * this->x) + (this->y * this->y));
    }
    
    Vec2 normalized()
    {
        if (magnitude() == 0) return *this;
        *this = *this / magnitude();
        return *this;
    }
};