#include "SuperPongConstants.h"
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const string GAME_NAME = "Super Pong";

const string IMG_PATH_L_PADDLE = "images/SP_paddle0000.png";
const string IMG_PATH_R_PADDLE = "images/SP_paddle0000.png";
const string IMG_PATH_BALL = "images/SP_ball0000.png";
const string TTF_PATH_SCORE_FONT = "fonts/courbd.ttf";

const SDL_Scancode L_PADDLE_UP_KEY = SDL_SCANCODE_W;
const SDL_Scancode L_PADDLE_DOWN_KEY = SDL_SCANCODE_S;
const SDL_Scancode R_PADDLE_UP_KEY = SDL_SCANCODE_UP;
const SDL_Scancode R_PADDLE_DOWN_KEY = SDL_SCANCODE_DOWN;
const SDL_Scancode START_BALL_KEY = SDL_SCANCODE_SPACE;
const SDL_Scancode QUIT_GAME_KEY = SDL_SCANCODE_ESCAPE;

const int DIRECTION_UP = 1;
const int DIRECTION_RIGHT = 2;
const int DIRECTION_DOWN = 3;
const int DIRECTION_LEFT = 4;

const int PADDLE_SPEED = 9;
const int BALL_SPEED = 4;

const int FRAME_PER_SECOND = 60; 