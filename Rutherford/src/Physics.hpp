#pragma once
#include "Vector.hpp"
#include "Particle.hpp"


namespace Coulomb{

    inline Vector* Force(Particle* p1, Particle* p2){
        // Coulomb force on p1 due to p2

        float k = (float)1e6;
        Vector r = *p1->pos - *p2->pos;

        float F = k * p1->q * p2->q / (r.mod()*r.mod());

        Vector* F_vec = new Vector();
        F_vec->mod(F);
        F_vec->ang(r.ang(false));
        return F_vec;
    }
}

namespace Gravity{

    inline Vector* Force(Particle* p1, Particle* p2){
        // Gravitational force on p1 due to p2

        float G = 1e8;
        Vector r = *p2->pos - *p1->pos;

        float F = G * p1->mass * p2->mass / (r.mod()*r.mod());

        Vector* F_vec = new Vector();
        F_vec->mod(F);
        F_vec->ang(r.ang(false));
        return F_vec;
    }
}


namespace Verlet{

    inline void Integrator(Particle* p, float dt){
        // Verlet integration
        *p->pos += *p->vel  *dt + *p->acc * 0.5 * dt*dt;
        *p->vel += *p->acc * dt;
    }
}

namespace Euler_ODE{
    
    inline void Integrator(Particle* p, float dt){
        // Euler ODE integration
        *p->pos += *p->vel * dt;
        *p->vel += *p->acc * dt;
    }
}

namespace RK4{

    inline void Integrator(Particle* p, float dt){
        // Runge-Kutta 4th order integration
        Vector k1_pos = *p->vel * dt;
        Vector k1_vel = *p->acc * dt;

        Vector k2_pos = (*p->vel + k1_vel*0.5f) * dt;
        Vector k2_vel = (*p->acc + k1_vel*0.5f) * dt;

        Vector k3_pos = (*p->vel + k2_vel*0.5f) * dt;
        Vector k3_vel = (*p->acc + k2_vel*0.5f) * dt;

        Vector k4_pos = (*p->vel + k3_vel) * dt;
        Vector k4_vel = (*p->acc + k3_vel) * dt;

        *p->pos += (k1_pos + k2_pos*2.f + k3_pos*2.f + k4_pos) / 6;
        *p->vel += (k1_vel + k2_vel*2.f + k3_vel*2.f + k4_vel) / 6;
    }
}