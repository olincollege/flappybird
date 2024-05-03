#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "../src/model.h"

// NOLINTBEGIN(*-magic-numbers)

/**
 * @brief Test to verify that the game ends when the bird collides with the
 * bottom of the top pipe.
 *
 * This test initializes the game state and bird's position to simulate a
 * scenario where the bird is positioned at the exact bottom edge of a top pipe.
 * The test checks if the collision detection function correctly identifies this
 * position as a collision, resulting in the game ending.
 *
 * @test
 *      - Initialize game state and bird to simulate collision with bottom of
 * top pipe.
 *      - Call the collision detection function.
 *      - Assert that the game is no longer playing, indicating a collision was
 * detected.
 */
Test(pipe_collision_tests, bottom_of_top_pipe) {
  GameState gameState;
  Bird bird;
  Pipe pipe;
  Pipes pipes;
  Timer end_timer;

  // Initialize game state and bird
  gameState.playing = TRUE;
  bird.y = 399;  // Bird is at the top of the pipe
  bird.x = 20;
  bird.width = 5;
  bird.height = 5;
  bird.y_vel = -5;
  bird.jumpBool = FALSE;

  pipe.x = (float)bird.x;
  pipe.topHeight = 400;
  pipe.width = 5;
  pipe.bottomHeight = 600;
  pipe.min_gap = 200;
  pipe.passed = FALSE;

  pipes.pipe[0] = pipe;

  // Call the function
  pipe_collision(&gameState, &bird, &pipes, &end_timer);

  // Assert that the game is no longer playing
  cr_assert_not(gameState.playing,
                "Game should end if bird touches the top of the pipe.");
}

/**
 * @brief Test to verify that the game ends when the bird collides with the top
 * of the bottom pipe.
 *
 * This test sets up the game state and bird's position to simulate a scenario
 * where the bird is positioned at the exact top edge of a bottom pipe. It
 * checks if the collision detection function correctly identifies this position
 * as a collision, resulting in the game ending.
 *
 * @test
 *      - Initialize game state and bird to simulate collision with top of
 * bottom pipe.
 *      - Call the collision detection function.
 *      - Assert that the game is no longer playing, indicating a collision was
 * detected.
 */
Test(pipe_collision_tests, top_of_bottom_pipe) {
  GameState gameState;
  Bird bird;
  Pipe pipe;
  Pipes pipes;
  Timer end_timer;

  // Initialize game state and bird
  gameState.playing = TRUE;
  bird.y = 400;  // Bird is at the bottom of the pipe
  bird.x = 20;
  bird.width = 5;
  bird.height = 5;
  bird.y_vel = -5;
  bird.jumpBool = FALSE;

  pipe.x = (float)bird.x;
  pipe.bottomHeight = 400;
  pipe.width = 5;
  pipe.topHeight = 200;
  pipe.min_gap = 200;
  pipe.passed = FALSE;

  pipes.pipe[0] = pipe;

  // Call the function
  pipe_collision(&gameState, &bird, &pipes, &end_timer);

  // Assert that the game is no longer playing
  cr_assert_not(gameState.playing,
                "Game should end if bird touches the bottom of the pipe.");
}

/**
 * @brief Test to verify that the game ends when the bird collides with the side
 * of a pipe.
 *
 * This test initializes the game state and sets the bird's position to simulate
 * a scenario where the bird is in contact with the side of a pipe. The test
 * evaluates if the collision detection function correctly identifies this as a
 * collision, thereby ending the game.
 *
 * @test
 *      - Initialize game state and bird to simulate collision with the side of
 * a pipe.
 *      - Call the collision detection function.
 *      - Assert that the game is no longer playing, indicating a collision was
 * detected.
 */
Test(pipe_collision_tests, side_of_pipe) {
  GameState gameState;
  Bird bird;
  Pipe pipe;
  Pipes pipes;
  Timer end_timer;

  // Initialize game state and bird
  gameState.playing = TRUE;
  bird.y = 300;  // Bird is at the bottom of the pipe
  bird.x = 20;
  bird.width = 5;
  bird.height = 5;
  bird.y_vel = -5;
  bird.jumpBool = FALSE;

  pipe.x = (float)bird.x + ((float)bird.width / 2);
  pipe.bottomHeight = 400;
  pipe.width = 5;
  pipe.topHeight = 200;
  pipe.min_gap = 200;
  pipe.passed = FALSE;

  pipes.pipe[0] = pipe;

  // Call the function
  pipe_collision(&gameState, &bird, &pipes, &end_timer);

  // Assert that the game is no longer playing
  cr_assert_not(gameState.playing,
                "Game should end if bird touches the side of the pipe.");
}

Test(pipe_collision_tests, no_collision) {
  GameState gameState;
  Bird bird;
  Pipe pipe;
  Pipes pipes;
  Timer end_timer;

  // Initialize game state and bird
  gameState.playing = TRUE;
  bird.y = 250;
  bird.width = 5;
  bird.height = 5;
  bird.y_vel = -5;
  bird.jumpBool = FALSE;
  bird.x = 20;

  pipe.x = 800;
  pipe.bottomHeight = 400;
  pipe.width = 5;
  pipe.topHeight = 200;
  pipe.min_gap = 200;
  pipe.passed = FALSE;

  pipes.pipe[0] = pipe;

  // Call the function
  pipe_collision(&gameState, &bird, &pipes, &end_timer);

  // Assert that the game is no longer playing
  cr_assert(gameState.playing,
            "Game should not end if bird does not collide with the pipe.");
}
// NOLINTEND(*-magic-numbers)
