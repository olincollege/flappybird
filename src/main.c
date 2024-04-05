#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "view.h"
#include "controller.h"
#include "model.h"

// #include "model.c"
// #include "controller.c"
// #include  "view.c"

// SDL_Window* window = NULL;
// SDL_Renderer* renderer = NULL;
// int running = NULL;

int initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return FALSE;
    }
    window = SDL_CreateWindow (
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );
    if  (!window) {
        fprintf(stderr, "Error creating SDL Window\n");
        return FALSE;
    }
    printf("window created\n");
    renderer = SDL_CreateRenderer(window, -1, 0);
      if  (!renderer) {
        fprintf(stderr, "Error creating SDL Renderer\n");
        return FALSE;
    }
    printf("renderer created\n");

    return TRUE;
}

void update() {

}

void destroy_window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main() {
    running = initialize_window();
    while (running == TRUE) {
        process_input();
        update();
        render();
    }
    return 0;
}
