#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "../src/model.h"  // Assuming the Bird structure and init functions are defined here

// NOLINTBEGIN(*-magic-numbers)

// Function to simulate the bird performing a jump at the end of a game
void simulate_end_game_jump(Bird* bird) {
  bird->y_vel = -BIRD_VEL;  // Simulate an upward jump
  bird->jumpBool = 1;       // Set jumping to true
}

// Test that the Bird is initialized with correct values
Test(bird_tests, bird_initializes_correctly) {
  Bird bird;
  init_bird(&bird);
  double expected = 0.001;

  cr_expect_eq(bird.x, BIRD_X_POS,
               "Bird x position should be initialized to BIRD_X_POS");
  cr_expect_float_eq(bird.y, BIRD_Y_POS, expected,
                     "Bird y position should be initialized to BIRD_Y_POS");
  cr_expect_eq(bird.width, BIRD_WIDTH,
               "Bird width should be initialized to BIRD_WIDTH");
  cr_expect_eq(bird.height, BIRD_HEIGHT,
               "Bird height should be initialized to BIRD_HEIGHT");
  cr_expect_float_eq(
      bird.y_vel, BIRD_VEL, expected,
      "Bird vertical velocity should be initialized to BIRD_VEL");
  cr_expect_eq(bird.jumpBool, FALSE,
               "Bird jumpBool should be initialized to FALSE");
}

// Test that the Bird resets correctly for a new game
Test(bird_tests, bird_resets_correctly_after_end_game) {
  Bird bird;
  init_bird(&bird);  // Initialize bird for the first game

  // Simulate end-game conditions where the bird might be jumping
  simulate_end_game_jump(&bird);

  // Now reset the bird for a new game
  init_bird(&bird);
  double expected = 0.001;

  // Verify that the bird has been reset to the correct initial values
  cr_assert_eq(bird.x, BIRD_X_POS, "Bird x position did not reset correctly");
  cr_assert_float_eq(bird.y, BIRD_Y_POS, expected,
                     "Bird y position did not reset correctly");
  cr_assert_eq(bird.width, BIRD_WIDTH, "Bird width did not reset correctly");
  cr_assert_eq(bird.height, BIRD_HEIGHT, "Bird height did not reset correctly");
  cr_assert_float_eq(bird.y_vel, BIRD_VEL, expected,
                     "Bird vertical velocity did not reset correctly");
  cr_assert_eq(bird.jumpBool, FALSE,
               "Bird jumpBool did not reset correctly after end game");
}
// NOLINTEND(*-magic-numbers)
