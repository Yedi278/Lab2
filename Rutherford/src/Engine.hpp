#include <SDL2/SDL.h>
#include "Particle.hpp"
#include <iostream>
#include <vector>

#define PARTICLE_COUNT 10


class Engine{

public:

    bool running = false;
    const char* title = "SDL2 Engine";

    Engine();
    ~Engine();

    int init();
    void handleEvents();
    void render();
    void update();
    void run();
    void shutdown();

private:

    std::vector<Particle> particles;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

};