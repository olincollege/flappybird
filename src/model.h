#pragma once

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum { FALSE, TRUE } Boolean;

enum { WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 1000 };

enum { BIRD_X_POS = 20, BIRD_Y_POS = 20, BIRD_WIDTH = 15, BIRD_HEIGHT = 15 };

enum { NUM_BLOCKS = 14, BLOCK_HEIGHT = 50, BLOCK_WIDTH = 100 };

enum {
  NUM_PIPES = 4,
  PIPE_SPACING = 300,    // Constant space between pipes, adjust as needed
  PIPE_GAP = 400,        // Vertical gap between pipes
  MIN_PIPE_HEIGHT = 50,  // Minimum height of the pipe parts
  PIPE_WIDTH = 100
};

extern const float BIRD_VEL;

extern const float GRAVITY;
extern const float START_GAMESPEED;
extern const float UPDATE_GAMESPEED;

typedef struct GameState {
  SDL_Window* window;
  SDL_Renderer* renderer;
  int running;
  int score;
  float gameSpeedx;
  int playing;
  int highScore;
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
  float topHeight;  // Height of the top pipe (bottom edge of the top pipe)
  float bottomY;    // Y position of the bottom pipe's top edge
  int width;
  float gap;
  int passed;
} Pipe;

typedef struct Pipes {
  Pipe pipe[NUM_PIPES];
} Pipes;

/**
 * Initialize the game state with default values.
 *
 * Sets initial values for the game state, including score, game speed, and the
 * running state. Sets the window and renderer pointers to NULL which
 * will be assigned when the SDL window and renderer are set up.
 *
 * @param gameState A pointer to the GameState structure to be initialized.
 */
void init_gameState(GameState* gameState);

/**
 * Initialize the bird structure with default values.
 *
 * This function sets the initial position, dimensions, and velocity of the
 * bird. It also ensures that the bird is not jumping by setting jumpBool to
 * FALSE.
 *
 * @param bird A pointer to the Bird structure to be initialized.
 */
void init_bird(Bird* bird);

/**
 * Initialize all ground blocks used in the game.
 *
 * This function sets up the ground blocks along the bottom of the game window.
 * Each block is positioned side by side with the specified width and height.
 * The ground blocks are decorative and mark the bottom border of the screen.
 *
 * @param ground A pointer to the Ground structure that contains all ground
 * blocks.
 */
void init_ground(Ground* ground);

/**
 * Initialize all pipes with random heights and positions.
 *
 * Pipes are spaced evenly along the horizontal axis and have random heights.
 * This function sets up each pipe's position, size, and the gap between them.
 *
 * @param pipes A pointer to the Pipes structure to initialize.
 */
void init_pipes(Pipes* pipes);

/**
 * Reset the game to its initial state.
 *
 * This function resets all game elements including the bird, ground, and pipes.
 * It also resets the game score and speed, and sets up the game for a new
 * playthrough.
 *
 * @param gameState A pointer to the GameState structure.
 * @param bird A pointer to the Bird structure.
 * @param pipes A pointer to the Pipes structure.
 * @param ground A pointer to the Ground structure.
 * @param timer A pointer to the Timer structure.
 */
void reset_gameplay(GameState* gameState, Bird* bird, Pipes* pipes,
                    Ground* ground, Timer* timer);

/**
 * Setup the initial game configuration.
 *
 * This function is a utility to initialize the bird, ground, and pipes
 * structures. It is typically called when resetting the game.
 *
 * @param bird A pointer to the Bird structure.
 * @param ground A pointer to the Ground structure.
 * @param pipes A pointer to the Pipes structure.
 */
void setup_inits(Bird* bird, Ground* ground, Pipes* pipes);

/**
 * Update the bird's position based on its velocity and gravity.
 *
 * This function adjusts the bird's position by applying gravity and any active
 * jumps. It also updates the jump timer to disable jumping at the right time.
 *
 * @param timer A pointer to the Timer controlling the jump duration.
 * @param bird A pointer to the Bird whose position and velocity are to be
 * updated.
 */
void update_bird(Timer* timer, Bird* bird);

/**
 * Update the position of all ground blocks to simulate movement.
 *
 * This function shifts all ground blocks to the left to create the effect of
 * the bird moving forward. Blocks that move past the left edge of the screen
 * are repositioned at the right end to create a continuous ground effect.
 *
 * @param gameState A pointer to the GameState containing the game's speed.
 * @param ground A pointer to the Ground structure whose blocks need to be
 * updated.
 */
void update_ground(GameState* gameState, Ground* ground);

/**
 * Update the position and status of all pipes to simulate movement.
 *
 * Pipes move left at the game speed, and pipes that exit the left edge of the
 * screen are recycled to the right with new random heights. This function
 * ensures continuous challenges by adjusting pipes positions and heights.
 *
 * @param gameState A pointer to the GameState containing the game's speed.
 * @param pipes A pointer to the Pipes structure that holds all pipe
 * information.
 */
void update_pipes(GameState* gameState, Pipes* pipes);

/**
 * Update the game score based on bird and pipe positions.
 *
 * As the bird passes each pipe, this function increments the score. If the
 * score reaches a certain threshold, it also triggers a speed increase. This
 * function is critical for scoring and game progression.
 *
 * @param gameState A pointer to the GameState to update the score.
 * @param pipes A pointer to the Pipes structure to determine if the bird has
 * passed a pipe.
 * @param bird A pointer to the Bird structure to check its position relative to
 * the pipes.
 */
void update_score(GameState* gameState, Pipes* pipes, Bird* bird);

/**
 * Ensure the bird does not exit the game area.
 *
 * This function checks if the bird has collided with the top or bottom
 * boundaries of the window. If a collision is detected, the game state is set
 * to not playing indicating that the game is over.
 *
 * @param gameState A pointer to the GameState.
 * @param bird The Bird structure to check for boundary collisions.
 */
void check_boundaries(GameState* gameState, Bird bird);

/**
 * Detect collisions between the bird and pipes.
 *
 * This function checks for intersections between the bird's rectangle and the
 * rectangles of the top and bottom parts of each pipe. If a collision is
 * detected, the game's playing state is set to FALSE indicating that the game
 * is over.
 *
 * @param gameState A pointer to the GameState to update the game state upon
 * collision.
 * @param bird The Bird structure (by value) representing the player's
 * character.
 * @param pipes The Pipes structure containing all pipes to check against the
 * bird.
 */
void pipe_collision(GameState* gameState, Bird bird, Pipes pipes);

/**
 * Increase the game's difficulty by speeding up the game elements.
 *
 * This function increases the horizontal speed of game elements and the bird's
 * vertical speed as the game progresses, facilitating a gradual increase in
 * difficulty.
 *
 * @param gameState A pointer to the GameState where the game speed is adjusted.
 * @param bird A pointer to the Bird structure where the vertical velocity is
 * increased.
 */
void increase_speed(GameState* gameState, Bird* bird);
