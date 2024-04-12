#include "view.h"

#define BLACK_COLOR_MAX 255

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, BLACK_COLOR_MAX);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
