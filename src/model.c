#include "model.h"

// void initialize_game_state(GameState* gameState) {
//     gameState->window = NULL;  // Will be set when creating a window
//     gameState->renderer = NULL; // Will be set when creating a renderer
//     gameState->running = TRUE;  // Gamestate is now running
// }

void update(Timer* timer, Bird* bird) {
  if (bird->jumpBool == TRUE) {
    bird->y -= 0.1;
  } else {
    bird->y += GRAVITY;
  }

  if ((timer->timerOn == TRUE) &&
      (SDL_GetTicks() - timer->startTime) > (timer->ms)) {
    bird->jumpBool = FALSE;
    timer->timerOn = FALSE;
  }
}

void checkBoundaries(GameState* gameState, Bird bird) {
  if ((bird.y <= 0) || (bird.y >= WINDOW_HEIGHT)) {
    gameState->running = FALSE;
  }
}

void init_ground(Ground* ground, int width, int height) {
    ground->x = 0;
    ground->y = WINDOW_HEIGHT - height;  // Position at bottom of the window
    ground->width = WINDOW_WIDTH;        // Span the entire window width
    ground->height = height;
}

void update_ground(GameState* gameState, Ground* ground) {
    // Move the ground to simulate motion, wrapping around the window
    ground->x -= 0.5;
    if (ground->x + ground->width < 0) {
        ground->x = 0;
    }
}

