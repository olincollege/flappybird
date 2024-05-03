add_library(model model.c model.h)
add_library(view view.c view.h)
add_library(controller controller.c controller.h)

add_executable(run_main main.c)
target_link_libraries(run_main model view controller ${SDL2_LIBRARIES})
target_link_libraries(view PRIVATE SDL2_ttf)
