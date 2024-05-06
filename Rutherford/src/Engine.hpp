#include <SDL2/SDL.h>
#include <iostream>

class Engine{

public:

    bool running = false;
    const char* title = "SDL2 Engine";

    Engine();
    ~Engine();

    int init();
    void handleEvents();
    void run();
    void shutdown();

private:

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

};