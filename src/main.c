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

int initialize_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    (void)fprintf(stderr, "Error initializing SDL.\n");
    return FALSE;
  }
  gameState.window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);

  if (!gameState.window) {
    (void)fprintf(stderr, "Error creating SDL Window\n");
    return FALSE;
  }
  printf("window created\n");

  gameState.renderer = SDL_CreateRenderer(gameState.window, -1, 0);
  if (!gameState.renderer) {
    (void)fprintf(stderr, "Error creating SDL Renderer\n");
    return FALSE;
  }
  printf("renderer created\n");

  return TRUE;
}

void destroy_window() {
  if (gameState.renderer) {
    SDL_DestroyRenderer(gameState.renderer);
    gameState.renderer = NULL;
  }
  if (gameState.window) {
    SDL_DestroyWindow(gameState.window);
    gameState.window = NULL;
  }
  SDL_Quit();
}


int main() {
  initialize_game_state(&gameState);
    setup(&bird, &ground, &pipes);
  gameState.running = initialize_window();
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
  destroy_window();
  return 0;
}
