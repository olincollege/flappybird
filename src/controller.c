#include "controller.h"

#include <SDL2/SDL.h>

void process_input_start(GameState* gameState, Timer* end_timer) {
  if ((SDL_GetTicks() - end_timer->startTime > end_timer->ms) &&
      end_timer->timerOn == TRUE) {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
      case SDL_QUIT:
        gameState->running = FALSE;
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          // quit the program on escape key press
          case SDLK_ESCAPE:
            gameState->running = FALSE;
            break;
          case SDLK_SPACE:
            gameState->playing = TRUE;
            end_timer->timerOn = FALSE;
            break;
        }
        break;
    }
  }
}

void process_input_gameplay(GameState* gameState, Bird* bird, Timer* timer) {
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type) {
    case SDL_QUIT:
      gameState->window = NULL;
      gameState->renderer = NULL;
      gameState->playing = FALSE;
      gameState->running = FALSE;
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        // quit the program on escape key press
        case SDLK_ESCAPE:
          gameState->window = NULL;
          gameState->renderer = NULL;
          gameState->playing = FALSE;
          gameState->running = FALSE;
          break;
        case SDLK_SPACE:
          jump(bird, timer);
          break;
      }
      break;
  }
}

void jump(Bird* bird, Timer* timer) {
  if (timer->timerOn == FALSE) {
    bird->jumpBool = TRUE;
    timer->timerOn = TRUE;
    timer->startTime = SDL_GetTicks();
    timer->ms = JUMP_TIME;
  }
}
