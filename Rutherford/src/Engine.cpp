#include "Engine.hpp"

Engine::Engine(){
    // Constructor
}

Engine::~Engine(){
    // Destructor
}

int Engine::init(){
    // Initialize the engine
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cerr << "SDL correctly initialized" << std::endl;
        return 0;
    }else{
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return -1;
    }
    return 1;

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

}

void Engine::run(){
    // Run the engine
    SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderPresent(renderer);

}

void Engine::shutdown(){
    // Shutdown the engine
    std::cout << "Shutting down the engine" << std::endl;   
    SDL_Quit();
}

void Engine::handleEvents(){
    SDL_Event event;
	SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        this->running = false;
        break;
    
    default:
        break;
    }
}