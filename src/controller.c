#include "controller.h"

void jump() {

}

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            running = FALSE;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym){
                // quit the program on escape key press
                case SDLK_ESCAPE:
                    running = FALSE;
                    break;
                case SDLK_SPACE:
                    jump();
                    break;
            }
            break;
    }   
}
