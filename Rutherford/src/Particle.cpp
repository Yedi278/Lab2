#include "Particle.hpp"

Particle::Particle()
{   
    pos = new Vector(0,0);
    vel = new Vector(0,0);
    acc = new Vector(0,0);

    if(pos == nullptr){
        SDL_Log("pos is nullptr");
    }
    if(vel == nullptr){
        SDL_Log("vel is nullptr");
    }
    if(acc == nullptr){
        SDL_Log("acc is nullptr");
    }
}

Particle::Particle(Vector* pos, Vector* vel, Vector* acc, float mass, float radius, float q)
{
    delete this->pos;
    delete this->vel;
    delete this->acc;
    
    this->pos = pos;
    this->vel = vel;
    this->acc = acc;

    this->mass = mass;
    this->radius = radius;
    this->q = q;    
}

Particle::~Particle(){
    delete pos;
    delete vel;
    delete acc;
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