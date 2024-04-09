#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#define FALSE 0
#define TRUE 1

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

// SDL_Window* window = NULL;
// SDL_Renderer* renderer = NULL;
// int running = NULL;

typedef struct GameState {
    SDL_Window* window;
    SDL_Renderer* renderer;
    int running;
} GameState;

// void initialize_game_state(GameState* gameState);
