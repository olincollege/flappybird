#include <SDL2/SDL.h>

#include "model.h"

// NOLINTBEGIN(*-magic-numbers)

typedef struct Text {
  SDL_Texture* texture;
  SDL_Surface* surface;
  SDL_Rect rect;
  char text[50];
  int x;
  int y;
} Text;

/**
 * Initialize the SDL window and renderer.
 *
 * This function sets up the SDL library, creates the game window, and
 * initializes the renderer. It returns TRUE if initialization is successful,
 * FALSE otherwise, providing basic error handling by outputting messages to
 * standard error.
 *
 * @param gameState A pointer to the GameState where the window and renderer are
 * stored.
 * @return Returns TRUE if the window and renderer were successfully
 * created, FALSE otherwise.
 */
Boolean initialize_window(GameState* gameState);

/**
 * Render the game state to the screen.
 *
 * This function clears the current rendering target with a black background,
 * renders the bird, the ground blocks, and the pipes. It ensures that all game
 * elements are visually updated on the screen.
 *
 * @param gameState A pointer to the GameState containing the renderer and other
 * game state information.
 * @param bird A pointer to the Bird structure containing the bird's properties
 * to be rendered.
 * @param ground A pointer to the Ground structure containing the ground blocks
 * to be rendered.
 * @param pipes A pointer ot the Pipes structure containing the pipes to be
 * rendered.
 */
void render_gameplay(GameState* gameState, Bird* bird, Ground* ground,
                     Pipes* pipes);

/**
 * Render the start screen of the game.
 *
 * This function is called to display the initial game screen before play
 * begins. It shows the score from the last game, the high score achieved by all
 * players, and the game instructions.
 *
 * @param gameState A pointer to the GameState containing the renderer.
 */
void render_start(GameState* gameState);

/**
 * Render text on the screen.
 *
 * This function is called to render text on the screen based on variables in
 * the Text struct.
 *
 * @param gameState A pointer to the GameState containing the renderer.
 * @param text A pointer to the Text struct containing the text to render and
 * its position.
 */
void render_text(GameState* gameState, Text* text);

/**
 * Render the score on the top right of the screen.
 *
 * This function is called to render the score on the screen.
 *
 * @param gameState A pointer to the GameState containing the renderer.
 * @param text A pointer to the Text struct containing the text to render and
 * its position.
 */
void render_score(GameState* gameState, Text* text);

/**
 * Render the high score on the start screen before/after each game.
 *
 * This function is called to render the high score on the start screen.
 *
 * @param gameState A pointer to the GameState containing the renderer and the
 * high score.
 */
void render_high_score(GameState* gameState);

/**
 * Destroy the SDL window and renderer and clean up SDL subsystems.
 *
 * This function destroys the created SDL window and renderer, and cleans up all
 * initialized SDL subsystems. It is typically called upon game exit to release
 * resources properly.
 *
 * @param gameState A pointer to the GameState containing the window and
 * renderer to destroy.
 */
void destroy_window(GameState* gameState);

// NOLINTEND(*-magic-numbers)
