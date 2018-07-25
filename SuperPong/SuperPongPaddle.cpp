#include "SuperPongPaddle.h"
#include "SuperPongConstants.h"
#include "HelperFunctions.h"

//PongPaddle functions: 
SuperPongPaddle::SuperPongPaddle() {
	this->x = 0;
	this->y = 0;
	this->surface = nullptr;
	this->speed = PADDLE_SPEED; 
}

SuperPongPaddle::SuperPongPaddle(int x, int y, SDL_Surface* surface) {
	this->x = x;
	this->y = y;
	this->surface = surface;
	this->speed = PADDLE_SPEED;
}

void SuperPongPaddle::setSurface(SDL_Surface* surface) {
	this->surface = surface;
}

void SuperPongPaddle::setCoordinates(int x, int y) {
	this->x = x;
	this->y = y;
}

int SuperPongPaddle::getX() {
	return x; 
}
int SuperPongPaddle::getY() {
	return y; 
}
void SuperPongPaddle::incrementScore() {
	this->score++; 
}
int SuperPongPaddle::getScore() {
	return score; 
}

SDL_Surface* SuperPongPaddle::getSurface() {
	return surface;
}

void SuperPongPaddle::move(int direction) {
	int diff = calculateValidYMovement(surface, y, speed, direction); 

	y += diff; 
}