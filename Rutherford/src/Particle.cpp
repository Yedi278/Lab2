#include "Particle.hpp"

Particle::Particle()
{
    this->pos = new Vector();
    this->vel = new Vector();
    this->acc = new Vector();

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
    SDL_SetRenderDrawColor(renderer, BLUE);
    SDL_RenderFillCircle(renderer, pos->x, pos->y, radius);

}

void Particle::render(SDL_Renderer* renderer, int r, int g, int b, int a){
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillCircle(renderer, pos->x, pos->y, radius);
}