#include "view.h"

#define BLACK 0, 0, 0, 255
#define RED 255, 0, 0, 255
#define DARK_GREEN 34, 139, 34, 255  // Define a color for the ground.
#define LIGHT_GREEN 50, 205, 50, 255

void render(GameState* gameState, Bird bird, Ground ground) {
    SDL_SetRenderDrawColor(gameState->renderer, BLACK);
    SDL_RenderClear(gameState->renderer);

    // Render the bird
    SDL_Rect bird_rect = {bird.x, (int)bird.y, bird.width, bird.height};
    SDL_SetRenderDrawColor(gameState->renderer, RED);
    SDL_RenderFillRect(gameState->renderer, &bird_rect);

    // Render each ground block with alternating colors
    for (int i = 0; i < NUM_BLOCKS; i++) {
        SDL_Rect ground_rect = {ground.blocks[i].x, (int)ground.blocks[i].y, ground.blocks[i].width, ground.blocks[i].height};
        if (i % 2 == 0) {
            SDL_SetRenderDrawColor(gameState->renderer, DARK_GREEN);
        } else {
            SDL_SetRenderDrawColor(gameState->renderer, LIGHT_GREEN);
        }
        SDL_RenderFillRect(gameState->renderer, &ground_rect);
    }

    SDL_RenderPresent(gameState->renderer);
}
