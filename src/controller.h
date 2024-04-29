#include <SDL2/SDL.h>

#include "model.h"

// Enumerations for game timing configurations
enum {
  JUMP_TIME = 500  // Duration in milliseconds that each jump lasts
};

/**
 * Handles the initial game setup and the transition from the start menu to the
 * game.
 *
 * This function waits for a 'SPACE' key press to begin the game from the start
 * state, setting up the game elements using `reset`. It also handles the
 * 'SDL_QUIT' and 'ESCAPE' keys to quit the game.
 *
 * @param gameState A pointer to the GameState to update the running state and
 * possibly start the game.
 * @param timer A pointer to the Timer to display the start page for at least two seconds.
 */
void process_input_start(GameState* gameState, Timer* end_timer);

/**
 * Processes user inputs to control the game state and the bird's movement.
 *
 * This function listens for SDL events and applies game logic based on user
 * inputs:
 * - 'SDL_QUIT' or 'ESCAPE' key: Exits the game by setting `running` and
 * `playing` to FALSE.
 * - 'SPACE' key: Initiates a jump action for the bird if not already jumping.
 *
 * @param gameState A pointer to the GameState to update the game's status.
 * @param bird A pointer to the Bird object to potentially initiate a jump.
 * @param timer A pointer to the Timer used to manage jump timing.
 */
void process_input_gameplay(GameState* gameState, Bird* bird, Timer* timer);

/**
 * Causes the bird to jump if not already in the middle of a jump.
 *
 * This function triggers a jump by setting the bird's `jumpBool` to TRUE,
 * marking the timer as active, and setting the start time to the current tick
 * count. The jump affects the bird's vertical movement in the update function.
 *
 * @param bird A pointer to the Bird structure to modify its jumping state.
 * @param timer A pointer to the Timer structure to start the jump timing.
 */
void jump(Bird* bird, Timer* timer);
