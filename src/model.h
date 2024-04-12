#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#define FALSE 0
#define TRUE 1

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

#define GRAVITY 1

// SDL_Window* window = NULL;
// SDL_Renderer* renderer = NULL;
// int running = NULL;

// void initialize_game_state(GameState* gameState);
typedef struct GameState {
    SDL_Window* window;
    SDL_Renderer* renderer;
    int running;
} GameState;

// bird struct
typedef struct Bird {
    int x;
    int y;
    int width;
    int height;
    int y_vel;
    int jumpBool;
} Bird;

// Timer struct
typedef struct Timer {
    Uint32 startTime;
    float ms;
    int timerOn;
} Timer;

