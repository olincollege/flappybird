#pragma once

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 1000

#define GRAVITY 0.05
#define START_GAMESPEED 0.1
#define UPDATE_GAMESPEED 0.1

#define BIRD_X_POS 20
#define BIRD_Y_POS 20
#define BIRD_WIDTH 15
#define BIRD_HEIGHT 15
#define BIRD_VEL 0.1

#define NUM_BLOCKS 14
#define BLOCK_HEIGHT 50
#define BLOCK_WIDTH 100

#define NUM_PIPES 4
#define PIPE_SPACING 300 // Constant space between pipes, adjust as needed
#define PIPE_GAP 400      // Vertical gap between pipes
#define MIN_PIPE_HEIGHT 50 // Minimum height of the pipe parts
#define PIPE_WIDTH 100


// void initialize_game_state(GameState* gameState);
typedef struct GameState {
  SDL_Window* window;
  SDL_Renderer* renderer;
  int running;
  int score;
  float gameSpeedx;
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

typedef struct GroundBlock {
    float x;
    float y;
    int width;
    int height;
} GroundBlock;

typedef struct Ground {
    GroundBlock blocks[NUM_BLOCKS];  // Define NUM_BLOCKS based on your needs
} Ground;

typedef struct Pipe {
    float x;
    float topHeight;    // Height of the top pipe (bottom edge of the top pipe)
    float bottomY;      // Y position of the bottom pipe's top edge
    int width;
    float gap; 
    int passed;
} Pipe;

typedef struct Pipes{
    Pipe pipe[NUM_PIPES];
} Pipes;

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


void init_ground(Ground* ground);

void update_ground(GameState* gameState, Ground* ground);

void init_pipes(Pipes* pipes);

void update_pipes(GameState* gameState, Pipes* pipes);

void pipe_collision(GameState* gameState, Bird bird, Pipes pipes);

void update_score(GameState* gameState, Pipes* pipes, Bird* bird);

void increase_speed(GameState* gameState, Bird* bird);
