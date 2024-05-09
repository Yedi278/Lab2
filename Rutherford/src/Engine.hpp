#include <SDL2/SDL.h>
#include "Particle.hpp"
#include <iostream>
#include <vector>

#define PARTICLE_COUNT 10


class Engine{

public:

    bool running = false;
    const char* title = "Rutherford Scattering Simulation";

    Engine();
    ~Engine();

    int init();
    void handleEvents();
    void render();
    void update();
    void shutdown();

    void addParticle();


    std::vector<Particle*> particles;

private:

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

};