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

extern SDL_Window* window;     // Declaration only
extern SDL_Renderer* renderer; // Declaration only
extern int running;           // Declaration only
