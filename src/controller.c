#include "controller.h"

void process_input_start(GameState* gameState, Bird* bird, Pipes* pipes,
                         Ground* ground, Timer* timer) {
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
          reset_gameplay(gameState, bird, pipes, ground, timer);
          break;
      }
      break;
  }
}

void process_input_gameplay(GameState* gameState, Bird* bird, Timer* timer) {
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type) {
    case SDL_QUIT:
      gameState->playing = FALSE;
      gameState->running = FALSE;
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        // quit the program on escape key press
        case SDLK_ESCAPE:
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
    timer->ms = TIME;
  }
}
