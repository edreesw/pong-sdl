#pragma once
#include "SDL.h"

class SuperPongPaddle {
	SDL_Surface* surface; 
	int x, y; 
	int score; 
	int speed;
public: 
	SuperPongPaddle(int, int, SDL_Surface*); 
	SuperPongPaddle(); 
	void setSurface(SDL_Surface*);
	void setCoordinates(int, int); 
	int getX();
	int getY(); 
	void incrementScore(); 
	int getScore(); 
	SDL_Surface* getSurface();
	
	void move(int); 
};