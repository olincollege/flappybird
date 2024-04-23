#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "../src/model.h"

// NOLINTBEGIN(*-magic-numbers)

// Definition for a test that checks if the bird at the boundary top ends the game
Test(boundary_tests, bird_at_top_boundary) {
    GameState gameState;
    Bird bird;
    
    // Initialize game state and bird
    gameState.playing = TRUE;
    bird.y = 0; // Bird is at the top of the window

    // Call the function
    check_boundaries(&gameState, bird);

    // Assert that the game is no longer playing
    cr_assert_not(gameState.playing, "Game should end if bird touches the top boundary.");
}

// Definition for a test that checks if the bird at the boundary bottom ends the game
Test(boundary_tests, bird_at_bottom_boundary) {
    GameState gameState;
    Bird bird;
    
    // Initialize game state and bird
    gameState.playing = TRUE;
    bird.y = WINDOW_HEIGHT - bird.height; // Bird is at the bottom of the window, assuming bird height

    // Call the function
    check_boundaries(&gameState, bird);

    // Assert that the game is no longer playing
    cr_assert_not(gameState.playing, "Game should end if bird touches the bottom boundary.");
}

// Definition for a test that checks if the bird within the safe zone continues the game
Test(boundary_tests, bird_within_safe_zone) {
    GameState gameState;
    Bird bird;
    
    // Initialize game state and bird
    gameState.playing = TRUE;
    bird.y = WINDOW_HEIGHT / 2; // Bird is safely within the middle of the window

    // Call the function
    check_boundaries(&gameState, bird);

    // Assert that the game is still playing
    cr_assert(gameState.playing, "Game should continue if bird is within safe bounds.");
}

// NOLINTEND(*-magic-numbers)
