#include <iostream>
#include <SDL2/SDL.h>
#include "Engine.hpp"
#include "Vector.hpp"
#undef main
#define FPS 60


Uint32 a = 0;

int main() {
    

    Engine* eng = new Engine();

    a = SDL_GetTicks();
    

    
    while (eng->running == true){
        
        // break;

        while(SDL_GetTicks() - a < 1000/FPS){
            
            eng->handleEvents();

        }

        eng->run();

        // std::cout << "FPS: " << 1000./float(SDL_GetTicks() - a) << '\n'; #print the FPS
        a = SDL_GetTicks();
    }
    eng->shutdown();

    return 0;
}