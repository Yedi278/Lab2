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

    // Create the proton
    try{
        proton = new Particle();
        if(proton == nullptr){
            throw "Error creating proton";
        }else{
            proton->pos->x = 600;
            proton->pos->y = HEIGHT/2;
            proton->q = 1;
            proton->radius = 10;
        }
    }
    catch(const char* msg){
        std::cerr << msg << std::endl;
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

void Engine::addElectron(float y){
    // Run the engine
    Particle* p = new Particle();
    p->pos->x = 10;
    p->pos->y = y;
    p->vel->x = 5;
    electrons.emplace_back(p);

}

Vector* F_coulomb(Particle* p1, Particle* p2){
    // Coulomb force on p1 due to p2
    
    float k = (float)1e5;
    Vector r = *p1->pos - *p2->pos;
    
    float F = k * p1->q * p2->q / (r.mod()*r.mod());
    
    // std::cout << "F: " << F << std::endl;
    Vector* F_vec = new Vector();
    F_vec->mod(F);
    F_vec->ang(r.ang(false));
    return F_vec;
}

void Verlet(Particle* p, float dt){
    // Verlet integration
    *p->pos += *p->vel + *p->acc * 0.5 * dt*dt;
    *p->vel += *p->acc * dt;
}


void Engine::update(float dt){
    // Update the engine physics
    for (auto part : electrons){

        // Update the electron
        Vector* F = F_coulomb(part, proton);
        
        // delete F;
        delete part->acc;
        part->acc = F;
        // std::cout << "F: " << F->x << ", " << F->y << std::endl;
        Verlet(part, dt);
    }

}

void Engine::render(){
    // Render the engine
    SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    Vector* v;
    for (auto part : electrons){
        part->render(renderer);
        v = F_coulomb(part, proton);
        SDL_RenderDrawArrow(renderer, *part->pos, *v, 1);
    }
    delete v;

    proton->render(renderer, RED);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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
    electrons.clear();
}

Engine::~Engine(){
    clean();
    shutdown();
}