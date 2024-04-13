#include "model.h"

/**
 * Handle user input
 *
 * This function handles user input, specifically, keyboard clicks. If the user
 * presses the escape key, it sets gameState->running to FALSE, and the window
 * is closed. If the user presses the space key, it calls jump(), which further
 * handles that event.
 *
 * @param gameState a pointer to an instance of GameState
 * @param bird a pointer to an instance of Bird
 * @param timer a pointer to an instance of Timer
 */
void process_input(GameState* gameState, Bird* bird, Timer* timer);

/**
 * Cause the bird to move up
 *
 * When called, bird.jumpBool is set to true, a timer is started, and the max
 * number of milliseconds to wait is set. This allows the update function to
 * move the bird up by a set number.
 *
 * @param bird a pointer to an instance of Bird
 * @param timer a pointer to an instance of Timer
 */
void jump(Bird* bird, Timer* timer);
