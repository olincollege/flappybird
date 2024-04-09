#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "controller.h"
#include "model.h"
#include "view.h"

GameState gameState;

void initialize_game_state() {
    gameState.window = NULL;  // Will be set when creating a window
    gameState.renderer = NULL; // Will be set when creating a renderer
    gameState.running = TRUE;  // Gamestate is now running
}

int initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        (void)fprintf(stderr, "Error initializing SDL.\n");
        return FALSE;
    }
    gameState.window = SDL_CreateWindow (
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );

    if  (!gameState.window) {
        (void)fprintf(stderr, "Error creating SDL Window\n");
        return FALSE;
    }
    printf("window created\n");

    gameState.renderer = SDL_CreateRenderer(gameState.window, -1, 0);
      if  (!gameState.renderer) {
        (void)fprintf(stderr, "Error creating SDL Renderer\n");
        return FALSE;
    }
    printf("renderer created\n");

    return TRUE;
}

void update() {

}

void destroy_window() {
    if (gameState.renderer) {
        SDL_DestroyRenderer(gameState.renderer);
        gameState.renderer = NULL;
    }
    if (gameState.window) {
        SDL_DestroyWindow(gameState.window);
        gameState.window = NULL;
    }
    SDL_Quit();
}

int main() {
    initialize_game_state();
    gameState.running = initialize_window();
    while (gameState.running) {
        process_input(&gameState); // Assume process_input now takes a pointer to gameState
        update();
        render(&gameState);
    }
    destroy_window();
    return 0;
}
