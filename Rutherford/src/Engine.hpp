#include <SDL2/SDL.h>
#include "Particle.hpp"
#include <iostream>
#include <vector>


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

    void addElectron();


    std::vector<Particle*> electrons;
    Particle* proton = new Particle(new Vector(0,0), new Vector(0, 0), new Vector(0, 0), 1000, 40, 4);

private:

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

};