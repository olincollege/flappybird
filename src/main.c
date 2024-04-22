#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "controller.h"
#include "model.h"
#include "view.h"

GameState gameState;
Bird bird;
Timer timer;
Ground ground;
Pipes pipes;

/**
 * The main entry point for the Flappy Bird game.
 *
 * This function initializes the game state, game window, and all game elements,
 * and then enters the main game loop. The game loop continues until the game
 * state indicates it should stop running. Within the game loop, the function
 * handles game start conditions, processes input, updates game elements, checks
 * interactions, and renders the updated game state until the game ends. Upon
 * exiting the loop, it cleans up resources by destroying the game window and
 * quitting SDL.
 *
 * @return int Returns 0 upon successful execution and shutdown of the game, or
 * another error code otherwise.
 */
int main() {
  // Initialize game state and game elements
  initialize_game_state(&gameState);
  setup(&bird, &ground, &pipes);

  // Initialize window and renderer, check for initialization success
  gameState.running = initialize_window(&gameState);

  // Main game loop: runs until 'running' is FALSE
  while (gameState.running == TRUE) {
    // Handle the start of the game, waiting for user to commence playing
    start_game(&gameState, &bird, &pipes, &ground, &timer);

    // Render start screen if not playing
    if (gameState.playing == FALSE) {
      render_start(&gameState);
    }

    // Gameplay loop: runs until 'playing' is FALSE
    while (gameState.playing == TRUE) {
      // Process user input (e.g., jumping and quitting)
      process_input(&gameState, &bird, &timer);

      // Update game elements
      update(&timer,
             &bird);  // Update bird's position based on jumping and gravity
      checkBoundaries(&gameState,
                      bird);  // Check for collisions with the screen edges
      update_ground(&gameState,
                    &ground);  // Update the position of the ground blocks
      update_pipes(&gameState,
                   &pipes);  // Update the positions and states of pipes
      pipe_collision(&gameState, bird,
                     pipes);  // Check for collisions between the bird and pipes
      update_score(&gameState, &pipes,
                   &bird);  // Update score based on bird passing pipes

      // Render updated game state
      render(&gameState, bird, ground, pipes);
    }
  }

  // Clean up resources and quit SDL
  destroy_window(&gameState);
  return 0;
}
