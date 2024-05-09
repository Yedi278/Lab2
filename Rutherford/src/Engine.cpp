#include "Engine.hpp"
#define WIDTH 800
#define HEIGHT 600

Engine::Engine(){
    // Constructor
    int val = init();   //control the initialization of the engine SDL parameters
    switch (val)
    {
        case 1:
            running = true;
            break;
        
        default:
            running = false;
            break;
    }
    
}

Engine::~Engine(){
    // Destructor
    // free( renderer);
    // free( window);
    // delete this;
}

int Engine::init(){
    // Initialize the engine
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cerr << "SDL correctly initialized" << std::endl;
    }else{
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);
    if(window == NULL){
        std::cerr << "Error creating window:"<< std::endl;
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer == NULL){
        std::cerr << "Error creating renderer:"<< std::endl;
        return -1;
    }
    return 1;
}

void Engine::addElectron(){
    // Run the engine
    Particle* p = new Particle();
    p->pos = new Vector(10, rand() % HEIGHT);
    electrons.emplace_back(p);

}

void Engine::update(){
    // Update the engine

    for (auto part : electrons){
        // Vector dst = proton->pos;
        std::cout << part << '\t' << (*part->pos - *proton->pos).x << std::endl;
        // std::cout << (*proton->pos - *part->pos).mod() << std::endl;
    }

}

void Engine::render(){
    // Render the engine
    SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for (auto part : electrons){
        part->render(renderer);
    }

    proton->render(renderer, RED);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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
        SDL_Log("Quit event detected, setting 'running' to false\n");
        break;
    
    default:
        break;
    }
}