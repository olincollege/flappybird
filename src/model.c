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

void update_ground(Ground* ground) {
    for (int i = 0; i < NUM_BLOCKS; i++) {
        ground->blocks[i].x -= 0.1;
        if (ground->blocks[i].x + ground->blocks[i].width < 0) {
            // Reposition to the right end
            int next_index = (i == 0 ? NUM_BLOCKS - 1 : i - 1);
            ground->blocks[i].x = ground->blocks[next_index].x + BLOCK_WIDTH;
        }
    }
}

void init_pipes(Pipes* pipes) {
    float initialX = WINDOW_WIDTH;
    for (int i = 0; i < NUM_PIPES; i++) {
        pipes->pipe[i].x = initialX + i * PIPE_SPACING;
        // Generate random heights for top and calculate bottom pipe start
        pipes->pipe[i].topHeight = (rand() % (WINDOW_HEIGHT - 2 * MIN_PIPE_HEIGHT - PIPE_GAP)) + MIN_PIPE_HEIGHT;
        pipes->pipe[i].bottomY = pipes->pipe[i].topHeight + PIPE_GAP;
        pipes->pipe[i].width = PIPE_WIDTH;
    }
}

void update_pipes(Pipes* pipes) {
     for (int i = 0; i < NUM_PIPES; i++) {
        pipes->pipe[i].x -= PIPE_MOVEMENT_SPEED;

        // Check if pipe has moved past the left edge of the screen
        if (pipes->pipe[i].x + pipes->pipe[i].width < 0) {
            int next_index = (i == NUM_PIPES - 1) ? 0 : i + 1;
            float rightMostX = pipes->pipe[next_index].x;

            // // Find the right-most pipe x position to place this pipe after it
            // for (int j = 0; j < NUM_PIPES; j++) {
            //     if (pipes->pipe[j].x > rightMostX) {
            //         rightMostX = pipes->pipe[j].x;
            //     }
            // }

            // pipes->pipe[i].x = rightMostX + PIPE_SPACING;
            pipes->pipe[i].x = WINDOW_WIDTH;
            // Randomly re-generate the heights for the recycled pipe
            pipes->pipe[i].topHeight = (rand() % (WINDOW_HEIGHT - 2 * MIN_PIPE_HEIGHT - PIPE_GAP)) + MIN_PIPE_HEIGHT;
            pipes->pipe[i].bottomY = pipes->pipe[i].topHeight + PIPE_GAP;
        }
    }
}
