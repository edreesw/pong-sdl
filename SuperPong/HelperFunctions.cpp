#include <stdlib.h>
#include <time.h>
#include <SDL.h> 
#include "SuperPongConstants.h"

int randomNumBetween(int min, int max) {
	return (rand() % ((max)-(min)+1)) + (min);
}



/**
	checks to see if the expected movement on the y axis will remain within the valid confines of the screen/window
	params: 
		surface - the surface that is being moved
		y - int marking where on the y axis the surface is being drawn
		speed - int representing amount of pixeled moved 
		direction - int representing direction moved, defined in SuperPongConstants.h
**/
int calculateValidYMovement(SDL_Surface* surface, int y, int speed, int direction) {
	int diff = 0; 

	if (direction == DIRECTION_UP) {
		if (y - speed < 0) {
			diff = -y; 
		}
		else {
			diff = -speed; 
		}
	}
	else if (direction == DIRECTION_DOWN) {
		if (y + speed + surface->h > SCREEN_HEIGHT) {
			diff = (SCREEN_HEIGHT - y) - surface->h; 
		}
		else {
			diff = speed; 
		}
	}

	return diff; 
}