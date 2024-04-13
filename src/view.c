#include "view.h"

#define BLACK 0, 0, 0, 255
#define RED 255, 0, 0, 255

void render(GameState* gameState, Bird bird) {
  SDL_SetRenderDrawColor(gameState->renderer, BLACK);
  SDL_RenderClear(gameState->renderer);

  SDL_Rect bird_rect = {bird.x, (int)bird.y, bird.width, bird.height};

  SDL_SetRenderDrawColor(gameState->renderer, RED);
  SDL_RenderFillRect(gameState->renderer, &bird_rect);

  SDL_RenderPresent(gameState->renderer);
}
