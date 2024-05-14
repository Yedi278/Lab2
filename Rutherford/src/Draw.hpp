#pragma once
#include "SDL.h"
#include "Vector.hpp"

#define RED 255, 0, 0, 255
#define GREEN 0, 255, 0, 255
#define BLUE 0, 0, 255, 255
#define WHITE 255, 255, 255, 255
#define BLACK 0, 0, 0, 255

int SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius);
int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);

void SDL_RenderDrawArrow(SDL_Renderer* renderer, Vector center, Vector v, float alpha);

// void SDL_RenderDrawGrid(SDL_Renderer* renderer, SDL_Window* window, int w_number, int h_number);