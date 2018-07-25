#include "SuperPongConstants.h"
#include "SuperPongPaddle.h"
#include "SuperPongBall.h"
#include "SDL.h"
#include "HelperFunctions.h"
#include <stdlib.h>
//PongBall functions:
SuperPongBall::SuperPongBall() {
	this->x = 0; 
	this->y = 0; 
	this->surface = nullptr; 
	this->speed = BALL_SPEED; 
}

SuperPongBall::SuperPongBall(int x, int y, SDL_Surface* surface) {
	this->x = x;
	this->y = y;
	this->surface = surface; 
	this->speed = BALL_SPEED;
}

void SuperPongBall::setSurface(SDL_Surface* surface) {
	this->surface = surface; 
}

void SuperPongBall::setCoordinates(int x, int y) {
	this->x = x; 
	this->y = y; 
}

bool SuperPongBall::isMoving() {
	return moving;
}
bool SuperPongBall::isOutOfBounds() {
	return outOfBounds; 
}
bool SuperPongBall::isPaddleHit() {
	return hitPaddle;
}

int SuperPongBall::currentXDirection() {
	return xDirection; 
}

int SuperPongBall::currentYDirection() {
	return yDirection; 
}

int SuperPongBall::getX() {
	return x; 
}
int SuperPongBall::getY() {
	return y; 
}

SDL_Surface* SuperPongBall::getSurface() {
	return surface; 
}

void SuperPongBall::reset() {
	x = (SCREEN_WIDTH / 2) - (surface->w / 2); 
	y = randomNumBetween(0, SCREEN_HEIGHT - surface->h); 
	outOfBounds = false; 
	xDirection = 0; 
	yDirection = 0; 
	speed = BALL_SPEED; 
	moving = false; 
}

void SuperPongBall::toggleMovementStart() {
	moving = true; 

	//set random direction
	if (rand() % 2 == 0) {
		if (rand() % 2 == 0) {
			yDirection = DIRECTION_UP; 
			xDirection = DIRECTION_RIGHT; 
		}
		else {
			yDirection = DIRECTION_DOWN; 
			xDirection = DIRECTION_RIGHT; 
		}
	}
	else {
		if (rand() % 2 == 0) {
			yDirection = DIRECTION_UP; 
			xDirection = DIRECTION_LEFT; 
		}
		else {
			yDirection = DIRECTION_DOWN; 
			xDirection = DIRECTION_LEFT; 
		}
	}
}

void SuperPongBall::resetPaddleHit() {
	hitPaddle = false; 
}

void SuperPongBall::changeToOppositeXDirection() {
	if (xDirection == DIRECTION_RIGHT) {
		xDirection = DIRECTION_LEFT; 
	}
	else {
		xDirection = DIRECTION_RIGHT; 
	}
}

void SuperPongBall::changeToOppositeYDirection() {
	if (yDirection == DIRECTION_UP) {
		yDirection = DIRECTION_DOWN; 
	}
	else {
		yDirection = DIRECTION_UP; 
	}
}

void SuperPongBall::increaseSpeed() {
	speed++; 
}

void SuperPongBall::move(SuperPongPaddle leftPaddle, SuperPongPaddle rightPaddle) {
	int diff = calculateValidYMovement(surface, y, speed, yDirection); 

	y += diff; 

	//if ball exceeds y axis bounds, reverse y direction
	if (abs(diff) != speed) {
		this->changeToOppositeYDirection(); 
	}

	hitPaddle = false;
	outOfBounds = false;

	if (xDirection == DIRECTION_LEFT) {
		x -= speed; 
		if (x < (leftPaddle.getX() + leftPaddle.getSurface()->w)) {
			if (y + surface->h < leftPaddle.getY() ||
				y > leftPaddle.getY() + leftPaddle.getSurface()->h) {
				outOfBounds = true; 
			}
			else {
				hitPaddle = true; 
				x = leftPaddle.getX() + leftPaddle.getSurface()->w; 
			}
		}
	}
	else if (xDirection == DIRECTION_RIGHT) {
		x += speed; 
		if (x + surface->w > rightPaddle.getX()) {
			if (y + surface->h < rightPaddle.getY() ||
				y > rightPaddle.getY() + rightPaddle.getSurface()->h) {
				outOfBounds = true; 
			}
			else {
				hitPaddle = true; 
				x = rightPaddle.getX() - surface->w; 
			}
		}
	}

}

