#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "../src/model.h"

// NOLINTBEGIN(*-magic-numbers)

/**
 * @brief Test to verify that the game ends when the bird touches the top
 * boundary of the game window.
 *
 * This test initializes the game state and sets the bird's y position to 0,
 * simulating the bird being at the top of the game window. It then calls the
 * function `check_boundaries` to determine if the game correctly identifies
 * this condition as a game-ending event.
 *
 * @test
 *      - Initialize game state to playing.
 *      - Set bird's y position to 0 (top boundary).
 *      - Assert that the game state is set to not playing after boundary check.
 */
Test(boundary_tests, bird_at_top_boundary) {
  GameState gameState;
  Bird bird;
  Timer end_timer;

  // Initialize game state and bird
  gameState.playing = TRUE;
  bird.y = 0;  // Bird is at the top of the window

  // Call the function
  check_boundaries(&gameState, &bird, &end_timer);

  // Assert that the game is no longer playing
  cr_assert_not(gameState.playing,
                "Game should end if bird touches the top boundary.");
}

/**
 * @brief Test to verify that the game ends when the bird touches the bottom
 * boundary of the game window.
 *
 * This test initializes the game state and sets the bird's y position to the
 * height of the window minus the bird's height, simulating the bird being at
 * the bottom of the game window. It then checks if the game correctly
 * identifies this condition as a game-ending event.
 *
 * @test
 *      - Initialize game state to playing.
 *      - Set bird's y position to window height minus bird height (bottom
 * boundary).
 *      - Assert that the game state is set to not playing after boundary check.
 */
Test(boundary_tests, bird_at_bottom_boundary) {
  GameState gameState;
  Bird bird;
  Timer end_timer;

  // Initialize game state and bird
  gameState.playing = TRUE;
  bird.y =
      WINDOW_HEIGHT -
      bird.height;  // Bird is at the bottom of the window, assuming bird height

  // Call the function
  check_boundaries(&gameState, &bird, &end_timer);

  // Assert that the game is no longer playing
  cr_assert_not(gameState.playing,
                "Game should end if bird touches the bottom boundary.");
}

/**
 * @brief Test to verify that the game continues when the bird is within the
 * safe zone of the game window.
 *
 * This test initializes the game state and sets the bird's y position to the
 * middle of the window, simulating the bird being in a safe zone. It then
 * checks if the game correctly continues without ending.
 *
 * @test
 *      - Initialize game state to playing.
 *      - Set bird's y position to the middle of the window (safe zone).
 *      - Assert that the game state is still set to playing after boundary
 * check.
 */
Test(boundary_tests, bird_within_safe_zone) {
  GameState gameState;
  Bird bird;
  Timer end_timer;

  // Initialize game state and bird
  gameState.playing = TRUE;
  bird.y = WINDOW_HEIGHT / 2;  // Bird is safely within the middle of the window

  // Call the function
  check_boundaries(&gameState, &bird, &end_timer);

  // Assert that the game is still playing
  cr_assert(gameState.playing,
            "Game should continue if bird is within safe bounds.");
}

// NOLINTEND(*-magic-numbers)
