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

int main() {
  initialize_game_state(&gameState);
    setup(&bird, &ground, &pipes);
  gameState.running = initialize_window(&gameState);
  while (gameState.running == TRUE) {
    start_game(&gameState, &bird, &pipes, &ground, &timer);
    if (gameState.playing == FALSE) {
      render_start(&gameState);
    }
    
    while (gameState.playing == TRUE) {
      process_input(
          &gameState, &bird,
          &timer);  // Assume process_input now takes a pointer to gameState
      update(&timer, &bird);
      checkBoundaries(&gameState, bird);
      update_ground(&gameState, &ground);  // Update the position of the ground
      update_pipes(&gameState, &pipes);
      pipe_collision(&gameState, bird, pipes);
      update_score(&gameState, &pipes, &bird);
      render(&gameState, bird, ground, pipes);  // Render bird and ground
    }
  }
  destroy_window(&gameState);
  return 0;
}
