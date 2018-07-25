#pragma once
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_ttf.h>

int randomNumBetween(int, int);

SDL_Surface* loadSurface(string, SDL_Surface*);

SDL_Surface* renderText(string, TTF_Font*); 

int blitSurfaceWithOffset(SDL_Surface*, SDL_Surface*, Sint16, Sint16); 

void capFPS(Uint32, Uint32);

int calculateValidYMovement(SDL_Surface*, int, int, int);