#include "model.h"


// Initial vertical velocity of the bird, controls how fast it rises on a jump.
const float BIRD_VEL = (float)0.15;

// Acceleration due to "gravity", applies a downward force to the bird's flight.
const float GRAVITY = (float)0.05;
// Initial horizontal speed of the game (i.e., speed of moving obstacles).
const float START_GAMESPEED = (float)0.1;
// Incremental increase in game speed each time a new point is scored.
const float UPDATE_GAMESPEED = (float)0.1;

void init_gameState(GameState* gameState) {
  gameState->window = NULL;    // Will be set when creating a window
  gameState->renderer = NULL;  // Will be set when creating a renderer
  gameState->running = TRUE;   // Gamestate is now running
  gameState->score = 0;
  gameState->gameSpeedx = START_GAMESPEED;
  gameState->playing = FALSE;
}

void init_bird(Bird* bird) {
  bird->x = BIRD_X_POS;
  bird->y = BIRD_Y_POS;
  bird->width = BIRD_WIDTH;
  bird->height = BIRD_HEIGHT;
  bird->y_vel = BIRD_VEL;
  bird->jumpBool = FALSE;
}

void init_ground(Ground* ground) {
  for (int i = 0; i < NUM_BLOCKS; i++) {
    ground->blocks[i].x = (float)i * BLOCK_WIDTH;
    ground->blocks[i].y = WINDOW_HEIGHT - BLOCK_HEIGHT;
    ground->blocks[i].width = BLOCK_WIDTH;
    ground->blocks[i].height = BLOCK_HEIGHT;
    // Optional: Set different colors or textures
  }
}

void init_pipes(Pipes* pipes) {
  unsigned int seed = (unsigned int)SDL_GetTicks;
  float initialX = WINDOW_WIDTH;
  for (int i = 0; i < NUM_PIPES; i++) {
    pipes->pipe[i].x = initialX + (float)i * PIPE_SPACING;
    // Generate random heights for top and calculate bottom pipe start
    pipes->pipe[i].topHeight =
        (float)(rand_r(&seed) %
                (WINDOW_HEIGHT - 2 * MIN_PIPE_HEIGHT - PIPE_GAP)) +
        MIN_PIPE_HEIGHT;
    pipes->pipe[i].bottomHeight = pipes->pipe[i].topHeight + PIPE_GAP;
    pipes->pipe[i].width = PIPE_WIDTH;
    pipes->pipe[i].passed = FALSE;
  }
}
void reset_gameplay(GameState* gameState, Bird* bird, Pipes* pipes,
                    Ground* ground, Timer* timer) {
  if (gameState->score > gameState->highScore) {
    gameState->highScore = gameState->score;
  }
  gameState->score = 0;
  gameState->gameSpeedx = START_GAMESPEED;
  setup_inits(bird, ground, pipes);
  timer->timerOn = FALSE;
  gameState->playing = TRUE;
}

void setup_inits(Bird* bird, Ground* ground, Pipes* pipes) {
  init_bird(bird);
  init_ground(ground);
  init_pipes(pipes);
}

void update_bird(Timer* timer, Bird* bird) {
  if (bird->jumpBool == TRUE) {
    bird->y -= bird->y_vel;
  } else {
    bird->y += GRAVITY + bird->y_vel;
  }

  if ((timer->timerOn == TRUE) &&
      (SDL_GetTicks() - timer->startTime) >
          (Uint32)(timer->ms)) {  // Convert to Uint32
    bird->jumpBool = FALSE;
    timer->timerOn = FALSE;
  }
}

void update_ground(GameState* gameState, Ground* ground) {
  for (int i = 0; i < NUM_BLOCKS; i++) {
    ground->blocks[i].x -= gameState->gameSpeedx;
    if (ground->blocks[i].x + (float)ground->blocks[i].width < 0) {
      // Reposition to the right end
      int next_index = (i == 0 ? NUM_BLOCKS - 1 : i - 1);
      ground->blocks[i].x = ground->blocks[next_index].x + BLOCK_WIDTH;
    }
  }
}

void update_pipes(GameState* gameState, Pipes* pipes) {
  for (int i = 0; i < NUM_PIPES; i++) {
    pipes->pipe[i].x -= gameState->gameSpeedx;

    // Check if pipe has moved past the left edge of the screen
    if (pipes->pipe[i].x + (float)pipes->pipe[i].width < 0) {
      // int next_index = (i == NUM_PIPES - 1) ? 0 : i + 1;
      // float rightMostX = pipes->pipe[next_index].x;
      pipes->pipe[i].x = WINDOW_WIDTH;
      // Randomly re-generate the heights for the recycled pipe
      pipes->pipe[i].topHeight =
          (float)(rand() % (WINDOW_HEIGHT - 2 * MIN_PIPE_HEIGHT - PIPE_GAP)) +
          MIN_PIPE_HEIGHT;
      pipes->pipe[i].bottomHeight = pipes->pipe[i].topHeight + PIPE_GAP;
    }
  }
}

void update_score(GameState* gameState, Pipes* pipes, Bird* bird) {
  for (int i = 0; i < NUM_PIPES; i++) {
    // Check if the pipe is just passing the bird's x position
    if (pipes->pipe[i].x + (float)pipes->pipe[i].width < (float)bird->x &&
        !pipes->pipe[i].passed) {
      gameState->score++;            // Increment score
      pipes->pipe[i].passed = TRUE;  // Mark this pipe as passed
      increase_speed(gameState, bird);
    }

    // Reset the pipe's passed flag if it has moved back to the right side of
    // the screen
    if (pipes->pipe[i].x > WINDOW_WIDTH) {
      pipes->pipe[i].passed = FALSE;
    }
  }
}

void check_boundaries(GameState* gameState, Bird bird) {
  if ((bird.y <= 0) || (bird.y >= WINDOW_HEIGHT - BLOCK_HEIGHT)) {
    gameState->playing = FALSE;
  }
}

void pipe_collision(GameState* gameState, Bird bird, Pipes pipes) {
  // Define the rectangle for the bird
  SDL_Rect bird_rect = {bird.x, (int)bird.y, bird.width, bird.height};

  for (int i = 0; i < NUM_PIPES; i++) {
    // Define the rectangle for the top part of the pipe
    SDL_Rect pipe_top_rect = {(int)pipes.pipe[i].x, 0, pipes.pipe[i].width,
                              (int)pipes.pipe[i].topHeight};

    // Define the rectangle for the bottom part of the pipe
    SDL_Rect pipe_bottom_rect = {
        (int)pipes.pipe[i].x, (int)pipes.pipe[i].bottomHeight,
        pipes.pipe[i].width, WINDOW_HEIGHT - (int)pipes.pipe[i].bottomHeight};

    // Check if the bird collides with the top or bottom pipe
    if (SDL_HasIntersection(&bird_rect, &pipe_top_rect) ||
        SDL_HasIntersection(&bird_rect, &pipe_bottom_rect)) {
      gameState->playing = FALSE;  // Collision detected, stop the game
      return;
    }
  }
}

void increase_speed(GameState* gameState, Bird* bird) {
  if (gameState->score % 2 == 0 && gameState->score != 0) {
    gameState->gameSpeedx += UPDATE_GAMESPEED;
    bird->y_vel += UPDATE_GAMESPEED;
  }
}
