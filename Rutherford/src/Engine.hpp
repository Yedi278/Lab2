#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <vector>
#include "Particle.hpp"
#include "Vector.hpp"

class Engine{

public:

    bool running = false;
    const char* title = "Rutherford Scattering Simulation";

    Engine();
    ~Engine();

    
    int init();
    void handleEvents();
    void render();
    void update(float dt);
    void shutdown();
    void clean();
    void addElectron(float y, float vo);

    std::vector<Particle*> electrons;
    Particle* proton = nullptr;

private:

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};