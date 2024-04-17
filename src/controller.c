#include "controller.h"

void jump(Bird* bird, Timer* timer) {
    bird->jumpBool = TRUE;
    timer->timerOn = TRUE;
    timer->startTime = SDL_GetTicks();
    timer->ms = TIME;
}

void process_input(GameState* gameState, Bird* bird, Timer* timer) {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            gameState->running = FALSE;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym){
                // quit the program on escape key press
                case SDLK_ESCAPE:
                    gameState->running = FALSE;
                    break;
                case SDLK_SPACE:
                    jump(bird, timer);
                    break;
            }
            break;
    }   
}

// 
// 
// 
// 
// 
// 

// is there a way to define the SDL_RECT once?
// 
// 
// 
// 
// 


// 

void pipe_collision(GameState* gameState, Bird bird, Pipes pipes) {
    // Define the rectangle for the bird
    SDL_Rect bird_rect = {bird.x, (int)bird.y, bird.width, bird.height};

    for (int i = 0; i < NUM_PIPES; i++) {
        // Define the rectangle for the top part of the pipe
        SDL_Rect pipe_top_rect = {pipes.pipe[i].x, 0, pipes.pipe[i].width, (int)pipes.pipe[i].topHeight};

        // Define the rectangle for the bottom part of the pipe
        SDL_Rect pipe_bottom_rect = {pipes.pipe[i].x, (int)pipes.pipe[i].bottomY, pipes.pipe[i].width, WINDOW_HEIGHT - (int)pipes.pipe[i].bottomY};

        // Check if the bird collides with the top or bottom pipe
        if (SDL_HasIntersection(&bird_rect, &pipe_top_rect) || SDL_HasIntersection(&bird_rect, &pipe_bottom_rect)) {
            gameState->running = FALSE; // Collision detected, stop the game
            return;
        }
    }
}
