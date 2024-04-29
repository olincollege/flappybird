#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "../src/model.h"

// NOLINTBEGIN(*-magic-numbers)

// Define a test that checks if the bird hits the bottom of the top pipe
Test(pipe_collision_tests, bottom_of_top_pipe) {
  GameState gameState;
  Bird bird;
  Pipe pipe;
  Pipes pipes;

  // Initialize game state and bird
  gameState.playing = TRUE;
  bird.y = 399;  // Bird is at the top of the pipe
  bird.x = 20;
  bird.width = 5;
  bird.height = 5;
  bird.y_vel = -5;
  bird.jumpBool = FALSE;

  pipe.x = bird.x;
  pipe.topHeight = 400;
  pipe.width = 5;
  pipe.bottomHeight = 600;
  pipe.min_gap = 200;
  pipe.passed = FALSE;

  pipes.pipe[0] = pipe;

  // Call the function
  pipe_collision(&gameState, bird, pipes);

  // Assert that the game is no longer playing
  cr_assert_not(gameState.playing,
                "Game should end if bird touches the top of the pipe.");
}

// Define a test that checks if the bird touches the top of the bottom pipe
Test(pipe_collision_tests, top_of_bottom_pipe) {
  GameState gameState;
  Bird bird;
  Pipe pipe;
  Pipes pipes;

  // Initialize game state and bird
  gameState.playing = TRUE;
  bird.y = 400;  // Bird is at the bottom of the pipe
  bird.x = 20;
  bird.width = 5;
  bird.height = 5;
  bird.y_vel = -5;
  bird.jumpBool = FALSE;

  pipe.x = bird.x;
  pipe.bottomHeight = 400;
  pipe.width = 5;
  pipe.topHeight = 200;
  pipe.min_gap = 200;
  pipe.passed = FALSE;

  pipes.pipe[0] = pipe;

  // Call the function
  pipe_collision(&gameState, bird, pipes);

  // Assert that the game is no longer playing
  cr_assert_not(gameState.playing,
                "Game should end if bird touches the bottom of the pipe.");
}

// Definition for a test that checks if the bird hits the side of a pipe
Test(pipe_collision_tests, side_of_pipe) {
  GameState gameState;
  Bird bird;
  Pipe pipe;
  Pipes pipes;

  // Initialize game state and bird
  gameState.playing = TRUE;
  bird.y = 300;  // Bird is at the bottom of the pipe
  bird.x = 20;
  bird.width = 5;
  bird.height = 5;
  bird.y_vel = -5;
  bird.jumpBool = FALSE;

  pipe.x = bird.x + (bird.width / 2);
  pipe.bottomHeight = 400;
  pipe.width = 5;
  pipe.topHeight = 200;
  pipe.min_gap = 200;
  pipe.passed = FALSE;

  pipes.pipe[0] = pipe;

  // Call the function
  pipe_collision(&gameState, bird, pipes);

  // Assert that the game is no longer playing
  cr_assert_not(gameState.playing,
                "Game should end if bird touches the side of the pipe.");
}

Test(pipe_collision_tests, no_collision) {
  GameState gameState;
  Bird bird;
  Pipe pipe;
  Pipes pipes;

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
  pipe_collision(&gameState, bird, pipes);

  // Assert that the game is no longer playing
  cr_assert(gameState.playing,
            "Game should not end if bird does not collide with the pipe.");
}
// NOLINTEND(*-magic-numbers)
