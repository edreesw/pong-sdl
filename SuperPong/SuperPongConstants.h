#pragma once
#include "SDL.h"
#include <string>
#include <iostream>
using namespace std;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const string GAME_NAME;

extern const string IMG_PATH_L_PADDLE; 
extern const string IMG_PATH_R_PADDLE;
extern const string IMG_PATH_BALL; 
extern const string TTF_PATH_SCORE_FONT; 

extern const SDL_Scancode L_PADDLE_UP_KEY; 
extern const SDL_Scancode L_PADDLE_DOWN_KEY;
extern const SDL_Scancode R_PADDLE_UP_KEY;
extern const SDL_Scancode R_PADDLE_DOWN_KEY;
extern const SDL_Scancode START_BALL_KEY;
extern const SDL_Scancode QUIT_GAME_KEY;

extern const int DIRECTION_UP; 
extern const int DIRECTION_RIGHT;
extern const int DIRECTION_DOWN;
extern const int DIRECTION_LEFT;

extern const int PADDLE_SPEED; 
extern const int BALL_SPEED; 

extern const int FRAME_PER_SECOND; 

