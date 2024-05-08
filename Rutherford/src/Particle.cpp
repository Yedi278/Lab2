#include "Particle.hpp"

Particle::Particle()
{
    this->pos =  Vector();
    this->vel =  Vector();
    this->acc =  Vector();

    this->q = 1;
    this->mass = 1;
    this->radius = 1;
}

Particle::Particle(Vector pos, Vector vel, Vector acc, float mass, float radius, float q)
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