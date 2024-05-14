#include "Engine.hpp"

#define WIDTH 1000
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

void Engine::addElectron(float y, float vo){
    // Run the engine
    Particle* p = new Particle();
    p->q = 1;
    p->pos->x = 10;
    p->pos->y = y;
    p->vel->x = vo;
    p->radius = 3;
    electrons.emplace_back(p);

}

void Engine::addNucleum(float x, float y){

    Particle* p = new Particle();
    p->pos->x = x;
    p->pos->y = y;
    p->q = 1;
    p->radius = 7;
    nucleus.emplace_back(p);

}

void Engine::update(float dt){
    // Update the engine physics
    for (auto part : electrons){

        Vector* F = new Vector(0,0);

        for(auto n : nucleus){
            Vector* F_c = Coulomb::Force(part, n);
            *F += *F_c;
            delete F_c;
        }

        // Update the particle's acceleration
        delete part->acc;
        part->acc = F;
        
        // Perform Verlet integration to update the particle's position and velocity
        Verlet::Integrator(part, dt);
        part->traces.push_back({part->pos->x, part->pos->y});
    }
}
 

void Engine::render(){
    // Render the engine
    
    // Clear the renderer
    SDL_RenderClear(renderer);
    
    // Set the draw color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    // Render the electrons and their Coulomb force vectors
    for (auto part : electrons){
        part->render(renderer);

        SDL_SetRenderDrawColor(renderer, RED);
        SDL_RenderDrawArrow(renderer, *part->pos, *part->vel, .1);

        SDL_SetRenderDrawColor(renderer, WHITE);

        if(show_trace){
            for (auto t : part->traces){
                SDL_RenderDrawPoint(renderer, t.x, t.y);
            }
        }
        
    }

    for(auto part : nucleus){
        part->render(renderer, RED);
    }

    // Set the draw color back to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    // Present the renderer
    SDL_RenderPresent(renderer);
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

    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        
        case SDLK_SPACE:
            paused = !paused;
            if(paused){
                std::cout << "Simulation paused" << std::endl;
            }
            else{
                std::cout << "Simulation resumed" << std::endl;
            }
            break;
        
        case SDLK_t:
            show_trace = !show_trace;
            if(show_trace){
                std::cout << "Traces enabled" << std::endl;
            }
            else{
                std::cout << "Traces disabled" << std::endl;
            }
            break;
        
        default:
            break;
        }
    default:
        break;
    }
}

void Engine::shutdown(){
    // Shutdown the engine
    std::cout << "Shutting down the engine" << std::endl;   
    SDL_Quit();
}

void Engine::clean(){
    // Clean the engine particles
    for (auto part : electrons){
        delete part;
    }
    for (auto part : nucleus){
        delete part;
    }
    electrons.clear();
    nucleus.clear();
}

Engine::~Engine(){
    clean();
    shutdown();
}