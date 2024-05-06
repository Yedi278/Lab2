#include <iostream>
#include <SDL2/SDL.h>
#include "Engine.hpp"

#define FPS 1


Uint32 a = 0;
Uint32 b = 0;

int main() {
    

    Engine* eng = nullptr;
    eng = new Engine();
    
    int init_param = eng->init();

    if (0 == init_param){
        eng->running = true;
    }

    while (eng->running == true){
        
        a = SDL_GetTicks();

        while(SDL_GetTicks() - a < 1000/FPS){
            
            eng->handleEvents();
            
        }
        eng->run();
    }
    eng->shutdown();

    return 0;
}