#include "view.h"

#define BLACK 0, 0, 0, 255
#define RED 255, 0, 0, 255
#define DARK_GREEN 34, 139, 34, 255  // Define a color for the ground.

void render(GameState* gameState, Bird bird, Ground ground) {
    SDL_SetRenderDrawColor(gameState->renderer, BLACK);
    SDL_RenderClear(gameState->renderer);

    // Render the bird
    SDL_Rect bird_rect = {bird.x, (int)bird.y, bird.width, bird.height};
    SDL_SetRenderDrawColor(gameState->renderer, RED);
    SDL_RenderFillRect(gameState->renderer, &bird_rect);

    // Render the ground
    SDL_Rect ground_rect = {ground.x, (int)ground.y, ground.width, ground.height};
    SDL_SetRenderDrawColor(gameState->renderer, DARK_GREEN);
    SDL_RenderFillRect(gameState->renderer, &ground_rect);

    SDL_RenderPresent(gameState->renderer);
}
