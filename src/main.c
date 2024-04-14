#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "controller.h"
#include "model.h"
#include "view.h"

GameState gameState;
Bird bird;
Timer timer;

void initialize_game_state() {
  gameState.window = NULL;    // Will be set when creating a window
  gameState.renderer = NULL;  // Will be set when creating a renderer
  gameState.running = TRUE;   // Gamestate is now running
}

void setup() {
  bird.x = BIRD_X_POS;
  bird.y = BIRD_Y_POS;
  bird.width = BIRD_WIDTH;
  bird.height = BIRD_HEIGHT;
  bird.y_vel = BIRD_VEL;
  bird.jumpBool = FALSE;
}

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

// void update() {
//   if (bird.jumpBool == TRUE) {
//     bird.y -= 0.1;
//   } else {
//     bird.y += GRAVITY;
//   }

//   if ((timer.timerOn == TRUE) &&
//       (SDL_GetTicks() - timer.startTime) > (timer.ms)) {
//     bird.jumpBool = FALSE;
//     timer.timerOn = FALSE;
//   }
// }

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
  initialize_game_state();
  setup();
  gameState.running = initialize_window();
  while (gameState.running == TRUE) {
    process_input(
        &gameState, &bird,
        &timer);  // Assume process_input now takes a pointer to gameState
    update(&timer, &bird);
    checkBoundaries(&gameState, bird);
    render(&gameState, bird);
  }
  destroy_window();
  return 0;
}
