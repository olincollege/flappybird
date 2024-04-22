# Flappy Bird
# SoftSys Final Project, Spring 2024
# Evelyn Kessler, Satchel Sevenau, Prisha Bhatia
An implementation of the videogame "Flappy Bird" in C using the SDL library.

## Installing Dependencies
This project uses the SDL library and associated SDL_Image and SDL_Text libraries to render the game. 

To install the appropriate libraries, run the following commands from a linux terminal.

Install SDL
'''
sudo ...
'''

Install SDL_Image
'''
sudo ...
'''

Install SDL_Text
'''
sudo ...
'''

Note that these libraries will not work properly on a virtual machine.

## How to Run
This project is compiled and run using CMake. If this is your first time playing, you will need to compile the code into a build folder. Starting in the main directory, enter the following commands to create the build folder and run cmake.
'''
mkdir build
cd build
cmake ..
make
'''
Now you will have all of the compiled files ready to go. You do not need to recompile every time; once your build folder is setup, you need only follow the instructions below to run the game.

Start the game from the build folder by running:
'''
src/run_main
'''

## Game Instructions
After running the commands above, you should see a pop-up screen with the flappy bird game start screen displayed. If you do not see a screen pop up, minimize other windows or check your taskbar for a new icon.

Press the spacebar to start the game and, once the game is running, to jump the bird. The game will end when the bird hits the top/bottom of the window or any pipe surface. After each game the screen will display the score from the latest game as well as the high score from all games played in this window. Press the spacebar to play again.

When you are done playing, use the esc key to destroy the pop-up window. Note that destroying the window will erase all data including the high score for this session. To create a new session, follow the instructions in "How to Run" to generate a new game window.
