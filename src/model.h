#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

// Define Boolean type for better readability.
typedef enum { FALSE, TRUE } Boolean;

// Set fixed dimensions for the game window
enum { WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 1000 };

// Bird's starting position and size
enum {
  BIRD_X_POS = 20,  // Horizontal start position of the bird
  BIRD_Y_POS = 20,  // Vertical start position of the bird
  BIRD_WIDTH = 15,  // Width of the bird
  BIRD_HEIGHT = 15  // Height of the bird
};

// Ground blocks settings, defining how many and their dimensions
enum {
  NUM_BLOCKS = 14,    // Number of ground blocks
  BLOCK_HEIGHT = 50,  // Height of each ground block
  BLOCK_WIDTH = 100   // Width of each ground block
};

// Pipes configuration for the obstacles
enum {
  NUM_PIPES = 4,       // Number of pipes, i.e., pairs of obstacles
  PIPE_SPACING = 300,  // Horizontal distance between consecutive pipes
  PIPE_GAP = 400,      // Vertical gap between the top and bottom parts of pipes
  MIN_PIPE_HEIGHT = 50,  // Minimum height of the pipe parts
  PIPE_WIDTH = 100       // Width of the pipes
};

// External declarations for physics constants. Values for constants defined in
// model.c
extern const float BIRD_VEL;  // Bird's vertical velocity (speed of flapping)
extern const float GRAVITY;   // Acceleration due to gravity (downward pull)
extern const float
    START_GAMESPEED;  // Initial speed of the game (speed of scrolling)
extern const float UPDATE_GAMESPEED;  // Speed increase per point scored

// Main game state structure, holding all relevant game status information
typedef struct GameState {
  SDL_Window* window;      // SDL Window for rendering
  SDL_Renderer* renderer;  // SDL Renderer associated with the window
  int running;             // Game running state flag (boolean)
  int score;               // Current score
  float gameSpeedx;        // Horizontal speed of game elements like pipes
  int playing;             // Is the game currently active (boolean)
  int highScore;           // Record of the highest score achieved
} GameState;

// Bird structure, represents the player's character
typedef struct Bird {
  int x;         // Horizontal position of the bird
  float y;       // Vertical position of the bird
  int width;     // Width of the bird
  int height;    // Height of the bird
  float y_vel;   // Current vertical velocity of the bird
  int jumpBool;  // Is the bird currently jumping (boolean)
} Bird;

// Timer structure for managing time-dependent events
typedef struct Timer {
  Uint32 startTime;  // Start time of the timer
  float ms;          // Duration for the timer in milliseconds
  int timerOn;       // Timer active state (boolean)
} Timer;

// Ground block structure, represents one horizontal block of the ground
typedef struct GroundBlock {
  float x;     // Horizontal position of the ground block
  float y;     // Vertical position of the ground block
  int width;   // Width of the ground block
  int height;  // Height of the ground block
} GroundBlock;

// Ground structure, contains all ground blocks
typedef struct Ground {
  GroundBlock blocks[NUM_BLOCKS];  // Array of ground blocks
} Ground;

// Pipe structure, represents one obstacle consisting of two vertical parts
typedef struct Pipe {
  float x;             // Horizontal position of both parts of the pipe
  float topHeight;     // Height from the top of the screen to the bottom of the
                       // top pipe
  float bottomHeight;  // Height from the bottom of the screen to the top of the
                       // bottom pipe
  int width;           // Width of the pipe (common for top and bottom parts)
  float min_gap;  // Minimum gap between the top and bottom pipes (derived from
                  // PIPE_GAP)
  int passed;     // Has the bird passed this pipe (for scoring)
} Pipe;

// Pipes structure, contains all pipes (obstacles)
typedef struct Pipes {
  Pipe pipe[NUM_PIPES];  // Array of pipes
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
