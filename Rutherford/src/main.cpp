#include <SDL.h>
#include <iostream>
#include <vector>
#include <memory>
#include <time.h>
#include "Engine.hpp"
#include "Vector.hpp"

#undef main
#define FPS 60

Uint32 a;

int main() {

    srand(time(0));

    Engine eng;

    float V_o = 6;

    eng.addElectron(200,V_o);
    eng.addElectron(240,V_o);
    eng.addElectron(250,V_o);
    eng.addElectron(300,V_o);

    a = SDL_GetTicks();
    
    while (eng.running == true){
        

        while(SDL_GetTicks() - a < 1000/FPS){
            
            eng.handleEvents();

        }

        eng.render();
        eng.update(0.01);

        // std::cout << "FPS: " << 1000./float(SDL_GetTicks() - a) << '\n'; #print the FPS
        a = SDL_GetTicks();

    }

    return 0;
}