#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "controller.h"
#include "model.h"
#include "view.h"

/**
 * The main entry point for the Flappy Bird game.
 *
 * This function initializes the game state, game window, and all game elements,
 * and then enters the main game loop to display the start screen. Once the game
 * is started, the function enters the gameplay loop. The gameplay loop
 * updates positions and renders the window, and continues until a collision
 * event is detected within the game. Within the game play loop, the function
 * handles game start conditions, processes input, updates game elements, checks
 * interactions, and renders the updated game state. Upon exiting the game play
 * loop the main game loop resets variables and sets the player up for a new
 * game. Upon exiting the main game loop, the function cleans up resources by
 * destroying the game window and quitting SDL.
 *
 * @return int Returns 0 upon successful execution and shutdown of the game, or
 * another error code otherwise.
 */
int main() {
  // Initialize the structs to store the game state, bird, timer for jumps,
  // ground, and the pipes.
  GameState gameState;
  Bird bird;
  Timer jump_timer;
  Ground ground;
  Pipes pipes;

  // Initialize the struct for the timer for the end of the game and fill it
  // with initial values. This timer is used to force a short pause on the start
  // game screen before the next game can be played; this pause avoids having
  // the player accidentally start a new game using the space bar when they
  // thought they were still jumping in the old game.
  Timer end_timer;
  end_timer.startTime = SDL_GetTicks();
  end_timer.ms = 1;
  end_timer.timerOn = TRUE;

  // Fill the gameState struct and the various game elements structs (bird,
  // ground, pipes) with their initial values.
  init_gameState(&gameState);
  setup_inits(&bird, &ground, &pipes);

  // Initialize window and renderer, check for initialization success.
  gameState.running = initialize_window(&gameState);

  // Main game loop: runs until 'running' is set to FALSE using the esc key.
  while (gameState.running == TRUE) {
    // Handle the start of the game, waiting for user to commence playing.
    reset_gameplay(&gameState, &bird, &pipes, &ground, &jump_timer);

    // Process user input on the start screen. ESC will exit the screen, SPACE
    // will start the game.
    process_input_start(&gameState, &end_timer);

    // Render start screen.
    render_start(&gameState);

    // Gameplay loop: runs until 'playing' is set to FALSE by a collision event.
    while (gameState.playing == TRUE) {
      // Process user input. ESC will exit the screen, SPACE will jump the bird.
      process_input_gameplay(&gameState, &bird, &jump_timer);

      // Update the bird's position based on jumping activity.
      update_bird(&jump_timer, &bird);

      // Check that the bird has not crossed the boundaries of the screen
      // (top/bottom); if it has, exit the gameplay loop.
      if (check_boundaries(&gameState, &bird, &end_timer) == FALSE) {
        break;
      }
      // Update the position of the ground blocks.
      update_ground(&gameState, &ground);
      // Update the positions and states of pipes.
      update_pipes(&gameState, &pipes);

      // Check that the bird has not collided with any pipes; if it has, exit
      // the gameplay loop.
      if (pipe_collision(&gameState, &bird, &pipes, &end_timer) == FALSE) {
        break;
      }

      // Update score when the bird successfully passes a pipe.
      update_score(&gameState, &pipes, &bird);

      // Render the game play.
      render_gameplay(&gameState, &bird, &ground, &pipes);
    }
  }

  // Clean up resources and quit SDL.
  destroy_window(&gameState);

  // If all setup and destroy operations successful, return 0.
  return 0;
}
