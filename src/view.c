#include "view.h"

#define BLACK 0, 0, 0, 255
#define RED 255, 0, 0, 255
#define DARK_GREEN 34, 139, 34, 255  // Define a color for the ground.
#define LIGHT_GREEN 50, 205, 50, 255
#define PIPE_DARK_GREEN 0, 100, 0, 255

void render(GameState* gameState, Bird bird, Ground ground, Pipes pipes) {
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

    // Render for each pipe
        for (int i = 0; i < NUM_PIPES; i++) {
        // Render the top part of the pipe
        SDL_Rect pipe_top_rect = {pipes.pipe[i].x, 0, pipes.pipe[i].width, (int)pipes.pipe[i].topHeight};
        SDL_SetRenderDrawColor(gameState->renderer, PIPE_DARK_GREEN);
        SDL_RenderFillRect(gameState->renderer, &pipe_top_rect);

        // Render the bottom part of the pipe
        SDL_Rect pipe_bottom_rect = {pipes.pipe[i].x, (int)(pipes.pipe[i].bottomY), pipes.pipe[i].width, WINDOW_HEIGHT - (int)pipes.pipe[i].bottomY};
        SDL_SetRenderDrawColor(gameState->renderer, PIPE_DARK_GREEN);
        SDL_RenderFillRect(gameState->renderer, &pipe_bottom_rect);
    }

    SDL_RenderPresent(gameState->renderer);
}
