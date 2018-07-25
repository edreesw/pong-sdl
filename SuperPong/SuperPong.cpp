#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "SuperPong.h"
#include "SuperPongPaddle.h"
#include "SuperPongBall.h"
#include "SuperPongConstants.h"
#include "HelperFunctions.h"
using namespace std;


int main(int argc, char* args[]) {
	SuperPong superPong;  

	if (!superPong.initialize()) {
		cout << "Failed to initialize!\n";
	}
	else if (!superPong.loadImages()) {
		cout << "Failed to load game images! IMG Error: " << IMG_GetError() << "\n"; 

	}
	else if (!superPong.setupScoreFont()) {
		cout << "Failed to setup score font! TTF Error: " << TTF_GetError() << "\n"; 
	} 
	else { 
		superPong.setupPongImageCoordinates(); 

		superPong.pongGameLoop(); 
	}
	
	SDL_Delay(3500);
	superPong.close();

	return 0; 
}
SuperPong::SuperPong() {
	mainWindow = nullptr;
	screenSurface = nullptr;
	scoreFont = nullptr;

}

bool SuperPong::initialize() {
	bool success = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL initialization failed! SDL_Error: " << SDL_GetError(); 
		success = false; 
	}
	else {
		//create the window
		mainWindow = SDL_CreateWindow(GAME_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (mainWindow == nullptr) {
			cout << "Window initialization failed! SDL_Error: " << SDL_GetError(); 
			success = false; 
		}
		else {
			screenSurface = SDL_GetWindowSurface(mainWindow); 
		}
	}
	return success; 
}


bool SuperPong::loadImages() {
	bool success = true;
	int imgFlags = IMG_INIT_PNG; 
	if (!(IMG_Init(IMG_INIT_PNG) & imgFlags)) {
		cout << "IMG initialization failed! IMG_Error: " << IMG_GetError(); 
		success = false; 

	}
	else {
		SDL_Surface* lPaddleSurface = loadSurface(IMG_PATH_L_PADDLE, screenSurface);
		SDL_Surface* rPaddleSurface = loadSurface(IMG_PATH_R_PADDLE, screenSurface);
		SDL_Surface* ballSurface = loadSurface(IMG_PATH_BALL, screenSurface);

		if (lPaddleSurface == nullptr || lPaddleSurface == nullptr || ballSurface == nullptr) {
			success = false;
		}

		lPaddle.setSurface(lPaddleSurface);
		rPaddle.setSurface(rPaddleSurface);
		ball.setSurface(ballSurface);
	}
	return success; 
}

bool SuperPong::setupScoreFont() {
	bool success = true; 
	if (TTF_Init() < 0) {
		cout << "TTF Init failed! TTF Error: " << TTF_GetError(); 
		success = false; 
	}
	else {
		scoreFont = TTF_OpenFont(TTF_PATH_SCORE_FONT.c_str(), 32);
		if (scoreFont == nullptr) {
			cout << "Font setup failed! TTF Error: " << TTF_GetError(); 
			success = false; 
		}
	}

	return success; 
}

void SuperPong::setupPongImageCoordinates() {
	lPaddle.setCoordinates(0, randomNumBetween(0, SCREEN_HEIGHT - lPaddle.getSurface()->h)); 

	rPaddle.setCoordinates(SCREEN_WIDTH - rPaddle.getSurface()->w, randomNumBetween(0, SCREEN_HEIGHT - rPaddle.getSurface()->h)); 

	ball.reset(); 
}

void SuperPong::pongGameLoop() {
	bool quit = false; 
	SDL_Event event; 

	Uint32 startTicks = 0, endTicks = 0;

	while (!quit) {
		startTicks = SDL_GetTicks(); 

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
				/*case SDL_KEYDOWN: */

			}
		}

		const Uint8 * keystate = SDL_GetKeyboardState(nullptr); 
		if (handleKeyboardState(keystate)) {
			quit = true; 
			break; 
		}

		if (ball.isMoving()) {
			ball.move(lPaddle, rPaddle); 
		}

		updateScreen(); 

		//handle collision on paddles or in the goal/score areas
		handleBallCollision(); 
		
		endTicks = SDL_GetTicks(); 
		capFPS(startTicks, endTicks); 
	}
}

bool SuperPong::handleKeyboardState(const Uint8* keystate) {
	bool quit_key = false; 
	
	if (keystate[QUIT_GAME_KEY]) {
		quit_key = true;
		return quit_key;
	}
	if(keystate[L_PADDLE_UP_KEY]) {
		lPaddle.move(DIRECTION_UP); 
	}
	if (keystate[L_PADDLE_DOWN_KEY]) {
		lPaddle.move(DIRECTION_DOWN); 
	}
	if (keystate[R_PADDLE_UP_KEY]) {
		rPaddle.move(DIRECTION_UP); 
	}
	if (keystate[R_PADDLE_DOWN_KEY]) {
		rPaddle.move(DIRECTION_DOWN); 
	}
	if (keystate[START_BALL_KEY]) {
		if (!ball.isMoving()) {
			ball.toggleMovementStart();
		}
	}

	return quit_key; 
}

void SuperPong::updateScreen() {
	//clear screen
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0, 0, 0)); 

	blitSurfaceWithOffset(lPaddle.getSurface(), screenSurface, lPaddle.getX(), lPaddle.getY()); 
	blitSurfaceWithOffset(rPaddle.getSurface(), screenSurface, rPaddle.getX(), rPaddle.getY()); 
	blitSurfaceWithOffset(ball.getSurface(), screenSurface, ball.getX(), ball.getY()); 
	drawScores(lPaddle.getScore(), rPaddle.getScore()); 

	SDL_UpdateWindowSurface(mainWindow); 
}


void SuperPong::drawScores(int leftScore, int rightScore) {
	string leftScoreText = to_string(leftScore); 
	string rightScoreText = to_string(rightScore); 

	SDL_Surface* leftScoreSurface = renderText(leftScoreText, scoreFont);
	SDL_Surface* rightScoreSurface = renderText(rightScoreText, scoreFont); 

	blitSurfaceWithOffset(leftScoreSurface, screenSurface, (SCREEN_WIDTH / 2) / 2 - leftScoreSurface->w / 2, 0); 
	blitSurfaceWithOffset(rightScoreSurface, screenSurface, ((SCREEN_WIDTH / 2) / 2) + (SCREEN_WIDTH / 2) - (rightScoreSurface->w / 2), 0); 

	SDL_FreeSurface(leftScoreSurface); 
	leftScoreSurface = nullptr; 
	SDL_FreeSurface(rightScoreSurface); 
	rightScoreSurface = nullptr; 
}


void SuperPong::handleBallCollision() {
	if (ball.isPaddleHit()) {
		ball.changeToOppositeXDirection(); 
		//TODO: add an up to date "movement" state to paddle, that shows if its moving up, down, or idle during the current loop. let this affect the direction (y axis) the ball bounces
		//for now, randomly change the y direction: 
		if (rand() % 2 == 0) { ball.changeToOppositeYDirection(); }
		ball.resetPaddleHit(); 
		//speed increment (?) TODO: add a toggle for increasing ball speed on every paddle hit
		ball.increaseSpeed(); 
	}
	else if (ball.isOutOfBounds()) {
		if (ball.currentXDirection() == DIRECTION_LEFT) {
			rPaddle.incrementScore(); 
		}
		else if (ball.currentXDirection() == DIRECTION_RIGHT) {
			lPaddle.incrementScore(); 
		}
		ball.reset(); 
	}
}




void SuperPong::close() {
	//deallocate memory to window
	SDL_DestroyWindow(mainWindow); 
	mainWindow = nullptr;

	SDL_FreeSurface(lPaddle.getSurface()); 
	lPaddle.setSurface(nullptr); 

	SDL_FreeSurface(rPaddle.getSurface()); 
	rPaddle.setSurface(nullptr); 

	SDL_FreeSurface(ball.getSurface()); 
	ball.setSurface(nullptr); 

	SDL_Delay(2000);

	if (TTF_WasInit()) {
		TTF_CloseFont(scoreFont); 
		TTF_Quit(); 
	}

	SDL_Quit(); 
}