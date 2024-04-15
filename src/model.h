#pragma once

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

#define GRAVITY 0.1

#define BIRD_X_POS 20
#define BIRD_Y_POS 20
#define BIRD_WIDTH 15
#define BIRD_HEIGHT 15
#define BIRD_VEL 0.5

// SDL_Window* window = NULL;
// SDL_Renderer* renderer = NULL;
// int running = NULL;

// void initialize_game_state(GameState* gameState);
typedef struct GameState {
  SDL_Window* window;
  SDL_Renderer* renderer;
  int running;
} GameState;

// bird struct
typedef struct Bird {
  int x;
  float y;
  int width;
  int height;
  float y_vel;
  int jumpBool;
} Bird;

// Timer struct
typedef struct Timer {
  Uint32 startTime;
  float ms;
  int timerOn;
} Timer;

typedef struct Ground {
    int x;
    float y;
    int width;
    int height;
} Ground;

void update(Timer* timer, Bird* bird);

/**
 * Check that the bird is within the boundaries of the window.
 *
 * If the bird hits the top or bottom of the screen, the game is over. The
 * function checks the y position of the bird and makes sure it is not touching
 * the screen boundaries. If it is, it sets the running variable in gameState to
 * false, and the game ends.
 *
 * @param gameState a pointer to the an instance of the GameState struct
 * @param bird a copy of the Bird struct
 */
void checkBoundaries(GameState* gameState, Bird bird);


void init_ground(Ground* ground, int width, int height);

void update_ground(GameState* gameState, Ground* ground);
