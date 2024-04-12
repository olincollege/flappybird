#include "controller.h"

void jump(Bird* bird, Timer* timer) {
    bird->jumpBool = TRUE;
    timer->timerOn = TRUE;
    timer->startTime = SDL_GetTicks();
    timer->ms = 500;
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
