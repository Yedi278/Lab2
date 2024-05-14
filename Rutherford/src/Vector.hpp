#pragma once
#include "math.h"

class Vector
{
    
public:

    float x;
    float y;

    Vector();
    Vector(float x, float y);

    float mod();
    void mod(float a);
    
    float ang(bool deg = false);
    void ang(float ang);

    void operator=(Vector v);
    
    Vector operator+(Vector v);
    Vector operator-(Vector v);
    
    Vector operator*(float s);
    // Vector operator*(int s);

    Vector operator/(float s);

    Vector operator+=(Vector v);
    Vector operator-=(Vector v);

    ~Vector();
};