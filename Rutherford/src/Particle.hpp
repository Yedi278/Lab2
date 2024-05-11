#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include "Vector.hpp"
#include "Draw.hpp"

class Particle
{
public:

    Vector* pos = new Vector(0,0);
    Vector* vel = new Vector(0,0);
    Vector* acc = new Vector(0,0);

    float mass = 1;
    float q = -1;
    float radius = 5;

    Particle();
    Particle(Vector* pos, Vector* vel, Vector* acc, float mass, float radius, float q);
    ~Particle();

    void render(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer, int r, int g, int b, int a);

};
