#include "Particle.hpp"

Particle::Particle()
{
    this->pos = new Vector();
    this->vel = new Vector();
    this->acc = new Vector();

    this->q = 1;
    this->mass = 1;
    this->radius = 1;
}

Particle::Particle(Vector* pos, Vector* vel, Vector* acc, float mass, float radius, float q)
{
    this->pos = pos;
    this->vel = vel;
    this->acc = acc;
    this->mass = mass;
    this->radius = radius;
    this->q = q;
}

Particle::~Particle()
{
    delete this;
}

void Particle::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDraw(renderer, pos->x, pos->y);
}