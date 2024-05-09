#pragma once
#include "Vector.hpp"
#include <SDL2/SDL.h>

class Particle
{

public:

    Vector* pos = nullptr;
    Vector* vel = nullptr;
    Vector* acc = nullptr;

    float mass = 1;
    float q = 1;
    float radius = 1;

    Particle();
    Particle(Vector* pos, Vector* vel, Vector* acc, float mass, float radius, float q);
    ~Particle();

    void render(SDL_Renderer* renderer);
};
