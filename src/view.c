#include "view.h"

#define BLACK_COLOR_MAX 255

void render(GameState* gameState) {
    SDL_SetRenderDrawColor(gameState->renderer, 0, 0, 0, BLACK_COLOR_MAX);
    SDL_RenderClear(gameState->renderer);
    SDL_RenderPresent(gameState->renderer);
}
