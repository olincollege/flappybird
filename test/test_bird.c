#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "../src/model.h"  // Assuming the Bird structure and init functions are defined here

// NOLINTBEGIN(*-magic-numbers)

/**
 * @brief Simulates an upward jump for the bird that goes all the way to the top
 * of the screen to end the game.
 *
 * This function modifies the bird's vertical velocity to simulate an upward
 * jump. It sets the bird's `jumpBool` flag to TRUE, indicating that a jump
 * is in progress.
 *
 * @param bird Pointer to the Bird struct that needs to perform the jump.
 */
void simulate_end_game_jump(Bird* bird) {
  bird->y_vel = -BIRD_VEL;  // Simulate an upward jump
  bird->jumpBool = TRUE;    // Set jumping to true
}

/**
 * @brief Test to verify if a Bird is initialized with correct default values.
 *
 * This test function checks whether all properties of the Bird struct are set
 * to their expected default values upon initialization. The expected values are
 * defined by constants such as BIRD_X_POS for the x position.
 *
 * @test
 *      - Verify that the bird's x position matches BIRD_X_POS.
 *      - Verify that the bird's y position matches BIRD_Y_POS with a precision
 * of 0.001.
 *      - Verify that the bird's width matches BIRD_WIDTH.
 *      - Verify that the bird's height matches BIRD_HEIGHT.
 *      - Verify that the bird's vertical velocity matches BIRD_VEL with a
 * precision of 0.001.
 *      - Verify that the bird's `jumpBool` is FALSE.
 */
Test(bird_tests, bird_initializes_correctly) {
  Bird bird;
  init_bird(&bird);

  cr_expect_eq(bird.x, BIRD_X_POS,
               "Bird x position should be initialized to BIRD_X_POS");
  cr_expect_float_eq(bird.y, BIRD_Y_POS, 0.001,
                     "Bird y position should be initialized to BIRD_Y_POS");
  cr_expect_eq(bird.width, BIRD_WIDTH,
               "Bird width should be initialized to BIRD_WIDTH");
  cr_expect_eq(bird.height, BIRD_HEIGHT,
               "Bird height should be initialized to BIRD_HEIGHT");
  cr_expect_float_eq(
      bird.y_vel, BIRD_VEL, 0.001,
      "Bird vertical velocity should be initialized to BIRD_VEL");
  cr_expect_eq(bird.jumpBool, FALSE,
               "Bird jumpBool should be initialized to FALSE");
}

/**
 * @brief Test to verify if the Bird struct resets correctly after the end of a
 * game.
 *
 * This test ensures that after simulating an end-game jump and resetting the
 * bird, all properties of the Bird struct are correctly reset to their initial
 * default values.
 *
 * @test
 *      - Simulate an end-game jump.
 *      - Reset the bird to initial state.
 *      - Verify all properties are reset as expected.
 */
Test(bird_tests, bird_resets_correctly_after_end_game) {
  Bird bird;
  init_bird(&bird);  // Initialize bird for the first game
  Bird bird;
  init_bird(&bird);  // Initialize bird for the first game

  // Simulate end-game conditions where the bird might be jumping
  simulate_end_game_jump(&bird);
  // Simulate end-game conditions where the bird might be jumping
  simulate_end_game_jump(&bird);

  // Now reset the bird for a new game
  init_bird(&bird);

  // Verify that the bird has been reset to the correct initial values
  cr_assert_eq(bird.x, BIRD_X_POS, "Bird x position did not reset correctly");
  cr_assert_float_eq(bird.y, BIRD_Y_POS, 0.001,
                     "Bird y position did not reset correctly");
  cr_assert_eq(bird.width, BIRD_WIDTH, "Bird width did not reset correctly");
  cr_assert_eq(bird.height, BIRD_HEIGHT, "Bird height did not reset correctly");
  cr_assert_float_eq(bird.y_vel, BIRD_VEL, 0.001,
                     "Bird vertical velocity did not reset correctly");
  cr_assert_eq(bird.jumpBool, FALSE,
               "Bird jumpBool did not reset correctly after end game");
}
// NOLINTEND(*-magic-numbers)
