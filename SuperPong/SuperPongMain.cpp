#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "SuperPongMain.h"
#include "SuperPongPaddle.h"
#include "SuperPongBall.h"
#include "SuperPongConstants.h"
#include "HelperFunctions.h"
using namespace std;

SDL_Window* mainWindow = nullptr;
SDL_Surface* screenSurface = nullptr;
TTF_Font* scoreFont = nullptr; 
//string testImagePath = "images/allMightIntense.jpg";

SuperPongPaddle lPaddle,  rPaddle;
SuperPongBall ball;



int main(int argc, char* args[]) {
	if (!initialize()) {
		cout << "Failed to initialize!\n";
	}
	else if (!loadImages()) {
		cout << "Failed to load game images! IMG Error: " << IMG_GetError() << "\n"; 

	}
	else if (!setupScoreFont()) {
		cout << "Failed to setup score font! TTF Error: " << TTF_GetError() << "\n"; 
	} 
	else { 
		setupPongImageCoordinates(); 

		pongGameLoop(); 
	}
	
	SDL_Delay(3500);
	close();

	return 0; 
}

bool initialize() {
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

SDL_Surface* loadSurface(string path) {
	SDL_Surface* loadedSurface = nullptr; 
	SDL_Surface* optimizedSurface = nullptr; 
	loadedSurface = IMG_Load(path.c_str()); //use png to carry over transparancy w/o having to introduce colorkey handling code
	if (loadedSurface == nullptr) {
		cout << "Loading image: " << path.c_str() << " failed! IMG_Error: " << IMG_GetError(); 
	}
	else {
		//optimize image
		optimizedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, 0); 
		if (optimizedSurface == nullptr) {
			cout << "Unable to optimize image! SDL Error: " << SDL_GetError();
		}

		SDL_FreeSurface(loadedSurface); 
		loadedSurface = nullptr; 
	}

	return optimizedSurface;
}

bool loadImages() {
	bool success = true;
	int imgFlags = IMG_INIT_PNG; 
	if (!(IMG_Init(IMG_INIT_PNG) & imgFlags)) {
		cout << "IMG initialization failed! IMG_Error: " << IMG_GetError(); 
		success = false; 

	}
	else {
		SDL_Surface* lPaddleSurface = loadSurface(IMG_PATH_L_PADDLE);
		SDL_Surface* rPaddleSurface = loadSurface(IMG_PATH_R_PADDLE);
		SDL_Surface* ballSurface = loadSurface(IMG_PATH_BALL);

		if (lPaddleSurface == nullptr || lPaddleSurface == nullptr || ballSurface == nullptr) {
			success = false;
		}

		lPaddle.setSurface(lPaddleSurface);
		rPaddle.setSurface(rPaddleSurface);
		ball.setSurface(ballSurface);
	}
	return success; 
}

bool setupScoreFont() {
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

void setupPongImageCoordinates() {
	lPaddle.setCoordinates(0, randomNumBetween(0, SCREEN_HEIGHT - lPaddle.getSurface()->h)); 

	rPaddle.setCoordinates(SCREEN_WIDTH - rPaddle.getSurface()->w, randomNumBetween(0, SCREEN_HEIGHT - rPaddle.getSurface()->h)); 

	ball.reset(); 
}

void pongGameLoop() {
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

bool handleKeyboardState(const Uint8* keystate) {
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

void updateScreen() {
	//clear screen
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0, 0, 0)); 

	blitSurfaceWithOffset(lPaddle.getSurface(), screenSurface, lPaddle.getX(), lPaddle.getY()); 
	blitSurfaceWithOffset(rPaddle.getSurface(), screenSurface, rPaddle.getX(), rPaddle.getY()); 
	blitSurfaceWithOffset(ball.getSurface(), screenSurface, ball.getX(), ball.getY()); 
	drawScores(lPaddle.getScore(), rPaddle.getScore()); 

	SDL_UpdateWindowSurface(mainWindow); 
}

int blitSurfaceWithOffset(SDL_Surface* srcSurface, SDL_Surface* screenSurface, Sint16 x, Sint16 y) {
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	return SDL_BlitSurface(srcSurface, nullptr, screenSurface, &offset);
}

void drawScores(int leftScore, int rightScore) {
	string leftScoreText = to_string(leftScore); 
	string rightScoreText = to_string(rightScore); 

	SDL_Surface* leftScoreSurface = renderText(leftScoreText);
	SDL_Surface* rightScoreSurface = renderText(rightScoreText); 

	blitSurfaceWithOffset(leftScoreSurface, screenSurface, (SCREEN_WIDTH / 2) / 2 - leftScoreSurface->w / 2, 0); 
	blitSurfaceWithOffset(rightScoreSurface, screenSurface, ((SCREEN_WIDTH / 2) / 2) + (SCREEN_WIDTH / 2) - (rightScoreSurface->w / 2), 0); 

	SDL_FreeSurface(leftScoreSurface); 
	leftScoreSurface = nullptr; 
	SDL_FreeSurface(rightScoreSurface); 
	rightScoreSurface = nullptr; 
}

SDL_Surface* renderText(string text) {
	SDL_Color color; 
	color.r = 204;
	color.g = 255;
	color.b = 255;
	return TTF_RenderText_Solid(scoreFont, text.c_str(), color); 
}

void handleBallCollision() {
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

void capFPS(Uint32 startTicks, Uint32 endTicks) {
	int delay = (1000 / FRAME_PER_SECOND) - (endTicks - startTicks); 

	if (delay > 0) {
		SDL_Delay(delay); 
	}
}

void close() {
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