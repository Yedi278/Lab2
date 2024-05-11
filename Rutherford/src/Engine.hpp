#include <SDL2/SDL.h>
#include "Particle.hpp"
#include "Vector.hpp"
#include <vector>
#include <memory>
#include <iostream>

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
    void clean();
    void addElectron();


    std::vector<Particle*> electrons;
    // Particle proton;

private:

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

};