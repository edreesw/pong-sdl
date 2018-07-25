#include <stdlib.h>
#include <time.h>
#include <SDL_ttf.h>
#include <SDL.h> 
#include <SDL_image.h>
#include "SuperPongConstants.h"

int randomNumBetween(int min, int max) {
	return (rand() % ((max)-(min)+1)) + (min);
}


SDL_Surface* loadSurface(string path, SDL_Surface* mainSurface) {
	SDL_Surface* loadedSurface = nullptr;
	SDL_Surface* optimizedSurface = nullptr;
	loadedSurface = IMG_Load(path.c_str()); //use png to carry over transparancy w/o having to introduce colorkey handling code
	if (loadedSurface == nullptr) {
		cout << "Loading image: " << path.c_str() << " failed! IMG_Error: " << IMG_GetError();
	}
	else {
		//optimize image
		optimizedSurface = SDL_ConvertSurface(loadedSurface, mainSurface->format, 0);
		if (optimizedSurface == nullptr) {
			cout << "Unable to optimize image! SDL Error: " << SDL_GetError();
		}

		SDL_FreeSurface(loadedSurface);
		loadedSurface = nullptr;
	}

	return optimizedSurface;
}


SDL_Surface* renderText(string text, TTF_Font* scoreFont) {
	SDL_Color color;
	color.r = 204;
	color.g = 255;
	color.b = 255;
	return TTF_RenderText_Solid(scoreFont, text.c_str(), color);
}

int blitSurfaceWithOffset(SDL_Surface* srcSurface, SDL_Surface* screenSurface, Sint16 x, Sint16 y) {
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	return SDL_BlitSurface(srcSurface, nullptr, screenSurface, &offset);
}

void capFPS(Uint32 startTicks, Uint32 endTicks) {
	int delay = (1000 / FRAME_PER_SECOND) - (endTicks - startTicks);

	if (delay > 0) {
		SDL_Delay(delay);
	}
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