#include "model.h"

/**
 * Create game screen and render objects onto the screen
 *
 * When called, the background screen is rendered. The bird rect
 * is created, and that is also rendered onto the screen.
 *
 * @param gameState a pointer to an instance of GameState
 * @param bird a copy of the instance of Bird
 */

void render(GameState* gameState, Bird bird, Ground ground, Pipes pipes);
