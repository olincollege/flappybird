#include "view.h"

const SDL_Color BLACK = {0, 0, 0, 255};
const SDL_Color RED = {255, 0, 0, 255};
const SDL_Color DARK_GREEN = {34, 139, 34, 255};
const SDL_Color LIGHT_GREEN = {50, 205, 50, 255};
const SDL_Color PIPE_DARK_GREEN = {0, 100, 0, 255};

int initialize_window(GameState* gameState) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    (void)fprintf(stderr, "Error initializing SDL.\n");
    return FALSE;
  }
  gameState->window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);

  if (!gameState->window) {
    (void)fprintf(stderr, "Error creating SDL Window\n");
    return FALSE;
  }
  printf("window created\n");

  gameState->renderer = SDL_CreateRenderer(gameState->window, -1, 0);
  if (!gameState->renderer) {
    (void)fprintf(stderr, "Error creating SDL Renderer\n");
    return FALSE;
  }
  printf("renderer created\n");

  return TRUE;
}

void render_gameplay(GameState* gameState, Bird bird, Ground ground,
                     Pipes pipes) {
  SDL_SetRenderDrawColor(gameState->renderer, BLACK.r, BLACK.g, BLACK.b,
                         BLACK.a);
  SDL_RenderClear(gameState->renderer);

  // Render the bird
  SDL_Rect bird_rect = {bird.x, (int)bird.y, bird.width, bird.height};
  SDL_SetRenderDrawColor(gameState->renderer, RED.r, RED.g, RED.b, RED.a);
  SDL_RenderFillRect(gameState->renderer, &bird_rect);

  // Render each ground block with alternating colors
  for (int i = 0; i < NUM_BLOCKS; i++) {
    SDL_Rect ground_rect = {ground.blocks[i].x, (int)ground.blocks[i].y,
                            ground.blocks[i].width, ground.blocks[i].height};
    if (i % 2 == 0) {
      SDL_SetRenderDrawColor(gameState->renderer, DARK_GREEN.r, DARK_GREEN.g,
                             DARK_GREEN.b, DARK_GREEN.a);
    } else {
      SDL_SetRenderDrawColor(gameState->renderer, LIGHT_GREEN.r, LIGHT_GREEN.g,
                             LIGHT_GREEN.b, LIGHT_GREEN.a);
    }
    SDL_RenderFillRect(gameState->renderer, &ground_rect);
  }

  // Render for each pipe
  for (int i = 0; i < NUM_PIPES; i++) {
    // Render the top part of the pipe
    SDL_Rect pipe_top_rect = {pipes.pipe[i].x, 0, pipes.pipe[i].width,
                              (int)pipes.pipe[i].topHeight};
    SDL_SetRenderDrawColor(gameState->renderer, PIPE_DARK_GREEN.r,
                           PIPE_DARK_GREEN.g, PIPE_DARK_GREEN.b,
                           PIPE_DARK_GREEN.a);
    SDL_RenderFillRect(gameState->renderer, &pipe_top_rect);

    // Render the bottom part of the pipe
    SDL_Rect pipe_bottom_rect = {
        pipes.pipe[i].x, (int)(pipes.pipe[i].bottomHeight), pipes.pipe[i].width,
        WINDOW_HEIGHT - (int)pipes.pipe[i].bottomHeight};
    SDL_SetRenderDrawColor(gameState->renderer, PIPE_DARK_GREEN.r,
                           PIPE_DARK_GREEN.g, PIPE_DARK_GREEN.b,
                           PIPE_DARK_GREEN.a);
    SDL_RenderFillRect(gameState->renderer, &pipe_bottom_rect);
  }

  SDL_RenderPresent(gameState->renderer);
}

void render_start(GameState* gameState) {
  SDL_SetRenderDrawColor(gameState->renderer, RED.r, RED.g, RED.b, RED.a);
  SDL_RenderClear(gameState->renderer);
  SDL_RenderPresent(gameState->renderer);
}

void destroy_window(GameState* gameState) {
  if (gameState->renderer) {
    SDL_DestroyRenderer(gameState->renderer);
    gameState->renderer = NULL;
  }
  if (gameState->window) {
    SDL_DestroyWindow(gameState->window);
    gameState->window = NULL;
  }
  SDL_Quit();
}
