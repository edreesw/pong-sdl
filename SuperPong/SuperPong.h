#pragma once
#include <time.h>
#include <string>
#include <iostream>
#include <SDL.h>
#include "SuperPongPaddle.h"
#include "SuperPongBall.h"
using namespace std;
//Basic SuperPong functions, implemented in main source file: 

class SuperPong {
	SDL_Window* mainWindow;
	SDL_Surface* screenSurface;
	TTF_Font* scoreFont;

	SuperPongPaddle lPaddle;
	SuperPongPaddle rPaddle;
	SuperPongBall ball;
public: 
	SuperPong(); 

	bool initialize();

	bool loadImages(); 

	bool setupScoreFont();

	void close();

	void setupPongImageCoordinates();

	void pongGameLoop();

	bool handleKeyboardState(const Uint8* keystate);

	void updateScreen();

	void handleBallCollision();

	void drawScores(int, int);


};

