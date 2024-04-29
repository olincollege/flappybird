#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <math.h>
#include <stdio.h>

#include "../src/model.h"

// NOLINTBEGIN(*-magic-numbers)

/**
 * @brief Test to verify that the bird's position updates correctly for a
 * downward drop.
 *
 * This test sets up the bird with an initial vertical position and velocity
 * directed downwards, then calls the `update_bird` function to process the
 * movement. The test checks if the bird's new position after the update
 * reflects the expected drop, accounting for the initial velocity and any
 * gravity effect included in the `update_bird` function.
 *
 * @test
 *      - Initialize bird with specific y position, downward velocity, and other
 * parameters.
 *      - Call the update function for the bird.
 *      - Assert the new y position is as expected, allowing for a small margin
 * of error.
 */
Test(bird_position_tests, bird_drop) {
  Bird bird;
  Timer timer;
  bird.y = 20;
  bird.y_vel = 5;
  bird.jumpBool = FALSE;
  bird.width = 5;
  bird.height = 5;
  bird.x = 5;

  update_bird(&timer, &bird);

  cr_assert(
      fabs(bird.y - 25.05 < 0.01),
      "Bird should drop by the specified amount when update_bird is called");
}

/**
 * @brief Test to verify that the bird's position updates correctly for an
 * upward jump.
 *
 * This test initializes a bird with an initial vertical position and velocity
 * directed upwards due to a jumping action. The `update_bird` function is then
 * called to process the bird's jump. The test evaluates whether the bird's new
 * position matches the expected elevation gain.
 *
 * @test
 *      - Initialize bird with specific y position, upward velocity, and set
 * jumpBool to TRUE.
 *      - Call the update function for the bird.
 *      - Assert the new y position is as expected, allowing for a small margin
 * of error.
 */
Test(bird_position_tests, bird_jump) {
  Bird bird;
  Timer timer;
  bird.y = 20;
  bird.y_vel = 5;
  bird.jumpBool = TRUE;
  bird.width = 5;
  bird.height = 5;
  bird.x = 5;

  update_bird(&timer, &bird);

  cr_assert(
      fabs(bird.y - 15 < 0.01),
      "Bird should jump by the specified amount when update_bird is called");
}

/**
 * @brief Test to verify that the pipe's position updates correctly when shifted
 * horizontally.
 *
 * This test sets up a single pipe with a starting x-position and a specified
 * game speed that affects how fast pipes move across the screen. The
 * `update_pipes` function is then called to process the pipe's movement. The
 * test checks if the new position of the pipe after the update matches the
 * expected displacement based on the game speed.
 *
 * @test
 *      - Initialize a pipe with specific x position and game speed.
 *      - Call the update function for pipes.
 *      - Assert the new x position of the pipe is as expected, allowing for a
 * small margin of error.
 */
Test(pipe_position_tests, pipe_shift) {
  Pipe pipe;
  Pipes pipes;
  GameState gameState;

  pipe.x = 500;
  pipe.bottomHeight = 400;
  pipe.width = 5;
  pipe.topHeight = 200;
  pipe.min_gap = 200;
  pipe.passed = FALSE;

  gameState.gameSpeedx = 30;
  pipes.pipe[0] = pipe;

  update_pipes(&gameState, &pipes);

  cr_assert(fabs(pipes.pipe[0].x - 470 < 0.01),
            "Pipe should move by the specified amount when update_pipe is "
            "called");
}

// NOLINTEND(*-magic-numbers)
