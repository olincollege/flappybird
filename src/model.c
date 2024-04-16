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
  if ((bird.y <= 0) || (bird.y >= WINDOW_HEIGHT - BLOCK_HEIGHT)) {
    gameState->running = FALSE;
  }
}

void init_ground(Ground* ground) {
    for (int i = 0; i < NUM_BLOCKS; i++) {
        ground->blocks[i].x = i * BLOCK_WIDTH;
        ground->blocks[i].y = WINDOW_HEIGHT - BLOCK_HEIGHT;
        ground->blocks[i].width = BLOCK_WIDTH;
        ground->blocks[i].height = BLOCK_HEIGHT;
        // Optional: Set different colors or textures
    }
}

void update_ground(GameState* gameState, Ground* ground) {
    for (int i = 0; i < NUM_BLOCKS; i++) {
        ground->blocks[i].x -= 0.1;
        if (ground->blocks[i].x + ground->blocks[i].width < 0) {
            // Reposition to the right end
            int next_index = (i == 0 ? NUM_BLOCKS - 1 : i - 1);
            ground->blocks[i].x = ground->blocks[next_index].x + BLOCK_WIDTH;
        }
    }
}
