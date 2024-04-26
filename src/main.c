#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "controller.h"
#include "model.h"
#include "view.h"

GameState gameState;
Bird bird;
Timer timer;
Ground ground;
Pipes pipes;

/**
 * The main entry point for the Flappy Bird game.
 *
 * This function initializes the game state, game window, and all game elements,
 * and then enters the main game loop. The game loop continues until the game
 * state indicates it should stop running. Within the game loop, the function
 * handles game start conditions, processes input, updates game elements, checks
 * interactions, and renders the updated game state until the game ends. Upon
 * exiting the loop, it cleans up resources by destroying the game window and
 * quitting SDL.
 *
 * @return int Returns 0 upon successful execution and shutdown of the game, or
 * another error code otherwise.
 */
int main() {
  // Initialize game state and game elements
  init_gameState(&gameState);
  setup_inits(&bird, &ground, &pipes);

  // Initialize window and renderer, check for initialization success
  gameState.running = initialize_window(&gameState);

  // Main game loop: runs until 'running' is FALSE
  while (gameState.running == TRUE) {
    // Handle the start of the game, waiting for user to commence playing
    process_input_start(&gameState, &bird, &pipes, &ground, &timer);

    // Render start screen if not playing
    if (gameState.playing == FALSE) {
      render_start(&gameState);
    }

    // Gameplay loop: runs until 'playing' is FALSE
    while (gameState.playing == TRUE) {
      // Process user input (e.g., jumping and quitting)
      process_input_gameplay(&gameState, &bird, &timer);

      // Update game elements
      update_bird(
          &timer,
          &bird);  // Update bird's position based on jumping and gravity
      check_boundaries(&gameState,
                       bird);  // Check for collisions with the screen edges
      update_ground(&gameState,
                    &ground);  // Update the position of the ground blocks
      update_pipes(&gameState,
                   &pipes);  // Update the positions and states of pipes
      pipe_collision(&gameState, bird,
                     pipes);  // Check for collisions between the bird and
      update_score(&gameState, &pipes,
                   &bird);  // Update score based on bird passing pipes
      // Render updated game state
      render_gameplay(&gameState, bird, ground, pipes);
    }
  }

  // Clean up resources and quit SDL
  destroy_window(&gameState);
  return 0;
}

// int main() {
//   // SDL_Surface* text;
//   // // Set color to black
//   // SDL_Color color = {0, 0, 0};

//   TTF_Font* Sans =
//       TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf",
//       24);
//   // text = TTF_RenderText_Solid(font, "Hello World!", color);
//   // if (!text) {
//   //   // cout << "Failed to render text: " << TTF_GetError() << endl;
//   //   printf("Failed to initialize \n");
//   // }
//   // this is the color in rgb format,
//   // maxing out all would give you the color white,
//   // and it will be your text's color
//   SDL_Color White = {255, 255, 255};

//   // as TTF_RenderText_Solid could only be used on
//   // SDL_Surface then you have to create the surface first
//   SDL_Surface* surfaceMessage =
//       TTF_RenderText_Solid(Sans, "put your text here", White);

//   // now you can convert it into a texture
//   SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer,
//   surfaceMessage);

//   SDL_Rect Message_rect;  // create a rect
//   Message_rect.x = 0;     // controls the rect's x coordinate
//   Message_rect.y = 0;     // controls the rect's y coordinte
//   Message_rect.w = 100;   // controls the width of the rect
//   Message_rect.h = 100;   // controls the height of the rect

//   // (0,0) is on the top left of the window/screen,
//   // think a rect as the text's box,
//   // that way it would be very simple to understand

//   // Now since it's a texture, you have to put RenderCopy
//   // in your game loop area, the area where the whole code executes

//   // you put the renderer's name first, the Message,
//   // the crop size (you can ignore this if you don't want
//   // to dabble with cropping), and the rect which is the size
//   // and coordinate of your texture
//   SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
// }
