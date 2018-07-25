#pragma once
#include "SDL.h"
#include "SuperPongPaddle.h"

class SuperPongBall {
	SDL_Surface* surface; 
	int x, y; 
	bool moving; 
	int xDirection; 
	int yDirection; 
	bool outOfBounds; 
	bool hitPaddle; 
	int speed; 

public: 
	SuperPongBall(int, int, SDL_Surface*); 
	SuperPongBall(); 
	void setSurface(SDL_Surface*);
	void setCoordinates(int, int);
	bool isMoving(); 
	bool isOutOfBounds(); 
	bool isPaddleHit(); 
	int currentXDirection(); 
	int currentYDirection(); 
	int getX(); 
	int getY(); 
	SDL_Surface* getSurface(); 

	void reset(); 
	void toggleMovementStart();
	void resetPaddleHit(); 
	void changeToOppositeXDirection(); 
	void changeToOppositeYDirection(); 
	void increaseSpeed(); 
	void move(SuperPongPaddle, SuperPongPaddle);

};