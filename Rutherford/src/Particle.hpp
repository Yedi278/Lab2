#pragma once
#include "Vector.hpp"

class Particle
{

public:

    Vector pos;
    Vector vel;
    Vector acc;

    float mass = 1;
    float q = 1;
    float radius = 1;

    Particle(/* args */);
    Particle(Vector pos, Vector vel, Vector acc, float mass, float radius, float q);
    ~Particle();
};
