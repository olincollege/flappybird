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
        ground->blocks[i].x -= gameState->gameSpeedx;
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
        pipes->pipe[i].passed = FALSE;
    }
}

void update_pipes(GameState* gameState, Pipes* pipes) {
     for (int i = 0; i < NUM_PIPES; i++) {
        pipes->pipe[i].x -= gameState->gameSpeedx;

        // Check if pipe has moved past the left edge of the screen
        if (pipes->pipe[i].x + pipes->pipe[i].width < 0) {
            int next_index = (i == NUM_PIPES - 1) ? 0 : i + 1;
            float rightMostX = pipes->pipe[next_index].x;
            pipes->pipe[i].x = WINDOW_WIDTH;
            // Randomly re-generate the heights for the recycled pipe
            pipes->pipe[i].topHeight = (rand() % (WINDOW_HEIGHT - 2 * MIN_PIPE_HEIGHT - PIPE_GAP)) + MIN_PIPE_HEIGHT;
            pipes->pipe[i].bottomY = pipes->pipe[i].topHeight + PIPE_GAP;
        }
    }
}

void pipe_collision(GameState* gameState, Bird bird, Pipes pipes) {
    // Define the rectangle for the bird
    SDL_Rect bird_rect = {bird.x, (int)bird.y, bird.width, bird.height};

    for (int i = 0; i < NUM_PIPES; i++) {
        // Define the rectangle for the top part of the pipe
        SDL_Rect pipe_top_rect = {pipes.pipe[i].x, 0, pipes.pipe[i].width, (int)pipes.pipe[i].topHeight};

        // Define the rectangle for the bottom part of the pipe
        SDL_Rect pipe_bottom_rect = {pipes.pipe[i].x, (int)pipes.pipe[i].bottomY, pipes.pipe[i].width, WINDOW_HEIGHT - (int)pipes.pipe[i].bottomY};

        // Check if the bird collides with the top or bottom pipe
        if (SDL_HasIntersection(&bird_rect, &pipe_top_rect) || SDL_HasIntersection(&bird_rect, &pipe_bottom_rect)) {
            gameState->running = FALSE; // Collision detected, stop the game
            return;
        }
    }
}

void update_score(GameState* gameState, Pipes* pipes, Bird bird) {
    for (int i = 0; i < NUM_PIPES; i++) {
        // Check if the pipe is just passing the bird's x position
        if (pipes->pipe[i].x + pipes->pipe[i].width < bird.x && !pipes->pipe[i].passed) {
            gameState->score++;  // Increment score
            pipes->pipe[i].passed = TRUE;  // Mark this pipe as passed
            increase_speed(gameState);
        }

        // Reset the pipe's passed flag if it has moved back to the right side of the screen
        if (pipes->pipe[i].x > WINDOW_WIDTH) {
            pipes->pipe[i].passed = FALSE;
        }
    }
}

void increase_speed(GameState* gameState) {
  if (gameState->score % 2 == 0 && gameState->score != 0) {
    gameState->gameSpeedx += UPDATE_GAMESPEED;
  }
}
