#include <SDL.h>
#include <iostream>
#include <memory>
#include <vector>
#include "Physics.hpp"
#include "Particle.hpp"
#include "Vector.hpp"

class Engine{

public:

    bool running = false;
    bool paused = true;
    bool show_trace = true;
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
    void addNucleum(float x,float y);

    std::vector<Particle*> electrons;
    std::vector<Particle*> nucleus;

private:

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};