#include "Draw.hpp"

void SDL_RenderDrawArrow(SDL_Renderer* renderer, Vector center, Vector v, float alpha){

    Vector sum = (v*alpha)+center;

    SDL_RenderDrawLine(renderer, center.x, center.y, sum.x, sum.y);
    
    Vector side = v*0.5;

    side.ang((float)(v.ang(false)-M_PI_2 -M_PI_4));
    SDL_RenderDrawLine(renderer, sum.x, sum.y, sum.x+side.x, sum.y+side.y);
    side.ang((float)(v.ang(false)+M_PI_2 +M_PI_4));
    SDL_RenderDrawLine(renderer, sum.x, sum.y, sum.x+side.x, sum.y+side.y);
}

int SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

// void SDL_RenderDrawGrid(SDL_Renderer* renderer, SDL_Window* window, int w_size, int h_size){

//     //get window size
//     int width, height;
//     SDL_GetWindowSize(window, &width, &height);

//     int w = width/w_size;
//     int h = height/h_size;


//     for(int i=0; i<w_size; i++){
//         SDL_RenderDrawLine(renderer, i*w, 0, i*w, height);
//     }
//     for(int i=0; i<h_size; i++){
//         SDL_RenderDrawLine(renderer, 0, i*h, width, i*h);
//     }

// }