#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "../src/controller.h"
#include "../src/model.h"
#include "../src/view.h"

// NOLINTBEGIN(*-magic-numbers)

/**
 * @brief Initializes a mock GameState and sets up an SDL Event to simulate an
 * ESC key press.
 *
 * This function prepares the game state to simulate a scenario where the game
 * is both running and actively being played. It also configures an SDL Event to
 * represent a keydown event for the ESC key, which is used to test the game's
 * response to this input.
 *
 * @param gameState Pointer to the GameState to initialize.
 * @param event Pointer to the SDL_Event to configure for the ESC key press
 * simulation.
 */
static void setup_esc_test(GameState* gameState, SDL_Event* event) {
  // Initialize game state
  init_gameState(gameState);
  gameState->running = TRUE;  // Game is running
  gameState->playing = TRUE;  // Game is actively being played

  // Set up an ESC keydown event
  event->type = SDL_KEYDOWN;
  event->key.keysym.sym = SDLK_ESCAPE;
}

/**
 * @brief Test to ensure that the game quits when the ESC key is pressed.
 *
 * This test uses the `setup_esc_test` function to initialize a mock GameState
 * and an SDL Event to simulate pressing the ESC key. The test checks if the
 * game state is updated correctly to stop running, which would indicate the
 * game is responding correctly to the ESC key press.
 *
 * @test
 *      - Setup the ESC key press simulation.
 *      - Process the simulated key press.
 *      - Assert that the game's running state is set to false.
 */
Test(esc_key_tests, esc_keypress_quits_game) {
  GameState gameState;
  SDL_Event event;
  
  // Setup the test environment
  setup_esc_test(&gameState, &event);

  // Process the input as the game would during normal operation
  SDL_PushEvent(&event);  // Simulate the event being in the event queue
  process_input_gameplay(&gameState, NULL, NULL);

  // Assert the game state reflects the game should stop running
  cr_assert_not(gameState.running, "Game should quit when ESC is pressed.");
}

/**
 * @brief Test to verify that all game resources are properly cleaned up upon
 * pressing the ESC key.
 *
 * This test initializes a game environment with a window and a renderer,
 * simulates an ESC key press, and checks if the cleanup process is executed
 * properly. The test ensures that the window and renderer are set to NULL,
 * indicating that they have been correctly disposed of after the key press.
 *
 * @test
 *      - Initialize game state and SDL resources.
 *      - Simulate an ESC key press and process the input.
 *      - Trigger the cleanup function.
 *      - Assert that all resources are set to NULL indicating proper cleanup.
 */
Test(esc_key_tests, cleanup_on_esc_keypress) {
  GameState gameState;
  SDL_Event event;

  // Setup the test environment with resources allocated
  setup_esc_test(&gameState, &event);
  gameState.window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_UNDEFINED,
                                      SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
  gameState.renderer =
      SDL_CreateRenderer(gameState.window, -1, SDL_RENDERER_ACCELERATED);

  // Process the input to trigger resource cleanup
  SDL_PushEvent(&event);  // Simulate the event being in the event queue
  process_input_gameplay(&gameState, NULL, NULL);
  destroy_window(&gameState);

  // Assert all resources are cleaned up
  cr_assert_null(gameState.window, "Window should be NULL after cleanup.");
  cr_assert_null(gameState.renderer, "Renderer should be NULL after cleanup.");
}

// NOLINTEND(*-magic-numbers)
