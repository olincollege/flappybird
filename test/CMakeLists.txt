# Some compilers warn that the return value of cr_assert gets converted from an
# int to a unsigned char:1. To avoid this error in those compilers, turn off
# conversion warnings for test code.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-conversion")

list(APPEND CMAKE_CTEST_ARGUMENTS --verbose)

add_executable(test_boundaries test_boundaries.c)
target_link_libraries(test_boundaries
    PRIVATE model
    PUBLIC ${CRITERION}
    ${SDL2_LIBRARIES}
)
add_test(
    NAME test_boundaries
    COMMAND test_boundaries ${CRITERION_FLAGS}
)

add_executable(test_pipe_collision test_pipe_collision.c)
target_link_libraries(test_pipe_collision
    PRIVATE model
    PUBLIC ${CRITERION}
    ${SDL2_LIBRARIES}
)
add_test(
    NAME test_pipe_collision
    COMMAND test_pipe_collision ${CRITERION_FLAGS}
)

add_executable(test_positions test_positions.c)
target_link_libraries(test_positions
    PRIVATE model m
    PUBLIC ${CRITERION}
    ${SDL2_LIBRARIES}
)
add_test(
    NAME test_positions
    COMMAND test_positions ${CRITERION_FLAGS}
)

add_executable(test_esc_key test_esc_key.c)
target_link_libraries(test_esc_key
    PRIVATE model controller view
    PUBLIC ${CRITERION}
    ${SDL2_LIBRARIES}
)
add_test(
    NAME test_esc_key
    COMMAND test_esc_key ${CRITERION_FLAGS}
)

add_executable(test_bird test_bird.c)
target_link_libraries(test_bird
    PRIVATE model
    PUBLIC ${CRITERION}
    ${SDL2_LIBRARIES}
)
add_test(
    NAME test_bird
    COMMAND test_bird ${CRITERION_FLAGS}
)
