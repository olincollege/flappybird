#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <math.h>
#include <stdio.h>

#include "../src/model.h"

// NOLINTBEGIN(*-magic-numbers)
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
