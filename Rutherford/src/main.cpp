#include <iostream>
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include "Engine.hpp"
#include "Vector.hpp"

#undef main
#define FPS 30

Uint32 a;

int main() {

    srand(time(0));

    Engine* eng = new Engine();

    a = SDL_GetTicks();
    
    eng->addElectron();
    eng->addElectron();
    eng->addElectron();
    eng->addElectron();

    
    while (eng->running == true){
        

        while(SDL_GetTicks() - a < 1000/FPS){
            
            eng->handleEvents();

        }

        eng->render();
        eng->update((float)(SDL_GetTicks() - a)/1000.0);

        // std::cout << "FPS: " << 1000./float(SDL_GetTicks() - a) << '\n'; #print the FPS
        a = SDL_GetTicks();
    }

    delete eng;
    return 0;
}