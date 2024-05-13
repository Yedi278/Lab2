#include "Vector.hpp"

Vector::Vector(){
    x = 0;
    y = 0;
}

Vector::Vector(float x, float y){
    this->x = x;
    this->y = y;
}

Vector::~Vector(){
    
}

void Vector::operator=(Vector v){
    x = v.x;
    y = v.y;   
}

Vector Vector::operator+(Vector v){
    return Vector(x + v.x, y + v.y);
}

Vector Vector::operator-(Vector v){
    return Vector(x - v.x, y - v.y);
}

Vector Vector::operator*(float s){
    float m = this->mod();
    float a = this->ang();
    return Vector(m * cos(a) * s, m * sin(a) * s);
}

Vector Vector::operator/(float s){
    return Vector(x / s, y / s);
}

float Vector::mod(){
    // returns the module of the vector
    return sqrt(x*x + y*y);
}

void Vector::mod(float a){
    // sets the module of the vector
    float ang = this->ang();
    this->x = a*cos(ang);
    this->y = a*sin(ang);
}

float Vector::ang(bool deg){
    // returns the angle of the vector in radians ->ang(true) or degrees ->ang()
    if(deg){
        return atan2(y, x)*(180./3.141592);
    }
    return atan2(y, x);
}

void Vector::ang(float ang){
    // sets the angle of the vector in radians
    float m = this->mod();
    this->x = m*cos(ang);
    this->y = m*sin(ang);
}

Vector Vector::operator+=(Vector v){
    x += v.x;
    y += v.y;
    return *this;
}

Vector Vector::operator-=(Vector v){
    x -= v.x;
    y -= v.y;
    return *this;
}