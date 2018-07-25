#pragma once
#include <time.h>
#include <string>
#include <iostream>
using namespace std;
//Basic SuperPong functions, implemented in main source file: 

bool initialize();

bool loadImages();

bool setupScoreFont();

void close();

void setupPongImageCoordinates();

void pongGameLoop();

SDL_Surface* loadSurface(string);

bool handleKeyboardState(const Uint8* keystate); 

void updateScreen(); 

void handleBallCollision(); 

int blitSurfaceWithOffset(SDL_Surface*, SDL_Surface*, Sint16, Sint16);

void drawScores(int, int); 

SDL_Surface* renderText(string); 

void capFPS(Uint32, Uint32); 