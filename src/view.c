#include "view.h"

#include <stdio.h>
#include <string.h>

// NOLINTBEGIN(*-magic-numbers)

const SDL_Color BLACK = {0, 0, 0, 255};
const SDL_Color RED = {255, 0, 0, 255};
const SDL_Color DARK_GREEN = {34, 139, 34, 255};
const SDL_Color LIGHT_GREEN = {50, 205, 50, 255};
const SDL_Color PIPE_DARK_GREEN = {0, 100, 0, 255};
const SDL_Color WHITE = {255, 255, 255, 255};

Boolean initialize_window(GameState* gameState) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    (void)fprintf(stderr, "Error initializing SDL.\n");
    return FALSE;
  }
  gameState->window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);

  if (!gameState->window) {
    (void)fprintf(stderr, "Error creating SDL Window\n");
    return FALSE;
  }
  printf("window created\n");

  gameState->renderer = SDL_CreateRenderer(gameState->window, -1, 0);
  if (!gameState->renderer) {
    (void)fprintf(stderr, "Error creating SDL Renderer\n");
    return FALSE;
  }
  printf("renderer created\n");
  if (TTF_Init() != 0) {
    (void)fprintf(stderr, "Error initializing TTF \n");
    return FALSE;
  }

  return TRUE;
}

void render_gameplay(GameState* gameState, Bird bird, Ground ground,
                     Pipes pipes) {
  SDL_SetRenderDrawColor(gameState->renderer, BLACK.r, BLACK.g, BLACK.b,
                         BLACK.a);
  SDL_RenderClear(gameState->renderer);

  // Render the bird
  SDL_Rect bird_rect = {bird.x, (int)bird.y, bird.width, bird.height};
  SDL_SetRenderDrawColor(gameState->renderer, RED.r, RED.g, RED.b, RED.a);
  SDL_RenderFillRect(gameState->renderer, &bird_rect);

  // Render each ground block with alternating colors
  for (int i = 0; i < NUM_BLOCKS; i++) {
    SDL_Rect ground_rect = {(int)ground.blocks[i].x, (int)ground.blocks[i].y,
                            ground.blocks[i].width, ground.blocks[i].height};
    if (i % 2 == 0) {
      SDL_SetRenderDrawColor(gameState->renderer, DARK_GREEN.r, DARK_GREEN.g,
                             DARK_GREEN.b, DARK_GREEN.a);
    } else {
      SDL_SetRenderDrawColor(gameState->renderer, LIGHT_GREEN.r, LIGHT_GREEN.g,
                             LIGHT_GREEN.b, LIGHT_GREEN.a);
    }
    SDL_RenderFillRect(gameState->renderer, &ground_rect);
  }

  // Render for each pipe
  for (int i = 0; i < NUM_PIPES; i++) {
    // Render the top part of the pipe
    SDL_Rect pipe_top_rect = {(int)pipes.pipe[i].x, 0, pipes.pipe[i].width,
                              (int)pipes.pipe[i].topHeight};
    SDL_SetRenderDrawColor(gameState->renderer, PIPE_DARK_GREEN.r,
                           PIPE_DARK_GREEN.g, PIPE_DARK_GREEN.b,
                           PIPE_DARK_GREEN.a);
    SDL_RenderFillRect(gameState->renderer, &pipe_top_rect);

    // Render the bottom part of the pipe
    SDL_Rect pipe_bottom_rect = {
        (int)pipes.pipe[i].x, (int)(pipes.pipe[i].bottomHeight),
        pipes.pipe[i].width, WINDOW_HEIGHT - (int)pipes.pipe[i].bottomHeight};
    SDL_SetRenderDrawColor(gameState->renderer, PIPE_DARK_GREEN.r,
                           PIPE_DARK_GREEN.g, PIPE_DARK_GREEN.b,
                           PIPE_DARK_GREEN.a);
    SDL_RenderFillRect(gameState->renderer, &pipe_bottom_rect);
  }

  Text score_text;
  render_score(gameState, &score_text);
  SDL_RenderPresent(gameState->renderer);
  SDL_DestroyTexture(score_text.texture);
  SDL_FreeSurface(score_text.surface);
}

void render_start(GameState* gameState) {
  SDL_SetRenderDrawColor(gameState->renderer, BLACK.r, BLACK.g, BLACK.b,
                         BLACK.a);
  SDL_RenderClear(gameState->renderer);
  Text start_message;
  char temp_text[40] = "Press SPACE to begin/jump & ESC to exit";
  strcpy(start_message.text, temp_text);
  start_message.x = WINDOW_WIDTH / 2;
  start_message.y = WINDOW_HEIGHT / 2;
  render_text(gameState, &start_message);
  render_high_score(gameState);
  SDL_RenderPresent(gameState->renderer);
}

void render_text(GameState* gameState, Text* text) {
  TTF_Font* Sans =
      TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf", 24);
  text->surface = TTF_RenderText_Solid(Sans, text->text, WHITE);
  text->texture =
      SDL_CreateTextureFromSurface(gameState->renderer, text->surface);
  text->rect.w = text->surface->w;  // controls the width of the rect
  text->rect.h = text->surface->h;
  text->rect.x =
      text->x - (text->rect.w / 2);  // controls the rect's x coordinate
  text->rect.y =
      text->y - (text->rect.h / 2);  // controls the height of the rect
  SDL_RenderCopy(gameState->renderer, text->texture, NULL, &text->rect);
}

void render_score(GameState* gameState, Text* text) {
  char score[50];
  sprintf(score, "%i", gameState->score);
  char your_score[50] = "Your Score: ";
  strcat(&your_score, &score);
  strcpy(text->text, your_score);
  text->x = WINDOW_WIDTH - 130;
  text->y = 50;
  render_text(gameState, text);
}

void render_high_score(GameState* gameState) {
  Text high_score_message;
  char high_score[50];
  sprintf(high_score, "%i", gameState->highScore);
  char temp_text[40] = "High Score: ";
  strcat(&temp_text, &high_score);
  strcpy(high_score_message.text, temp_text);
  high_score_message.x = WINDOW_WIDTH / 2;
  high_score_message.y = (WINDOW_HEIGHT / 2) + 25;
  render_text(gameState, &high_score_message);
}

void destroy_window(GameState* gameState) {
  if (gameState->renderer) {
    SDL_DestroyRenderer(gameState->renderer);
    gameState->renderer = NULL;
  }
  if (gameState->window) {
    SDL_DestroyWindow(gameState->window);
    gameState->window = NULL;
  }
  SDL_Quit();
}

// NOLINTEND(*-magic-numbers)
