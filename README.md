# Flappy Bird - SoftSys Final Project, Spring 2024
### Evelyn Kessler, Satchel Sevenau, Prisha Bhatia
An implementation of the videogame "Flappy Bird" in C using the SDL library.

## Installing Dependencies
This project uses the SDL Library and the associated SDL Text Library to render the game. 

To install the appropriate libraries, run the following commands from a linux terminal. You must install both libraries before running the game.

Install SDL
```
sudo apt-get install libsdl2-dev
```
The SDL Library is a cross-platform development library for writing computer games in C. This command will install the appropriate version, SDL 2. SDL 2.0 and above is available under the zlib license from https://www.libsdl.org/.


Install SDL_Text
```
sudo apt-get install libsdl2-ttf-dev 
```
The SDL Text Library works in conjunction with the SDL Library to render text using TrueType fonts. SDL_ttf 2.0 is available under the zlib license from https://wiki.libsdl.org/SDL2_ttf/. 

Note that the SDL library may not work properly on a virtual machine.

## How to Run
The first thing you'll need to do is change the file path in the view.c folder on line 112. Run the following in the terminal, and then replace the file path in the TTF_OpenFont function with yours. 
```
fc-list | grep DejaVu
```

This project is compiled and run using CMake. If this is your first time playing, you will need to compile the code into a build folder. Starting in the main directory, enter the following commands to create the build folder and run cmake.
```
mkdir build
cd build
cmake ..
make
```
Now you will have all of the compiled files ready to go. You do not need to recompile every time; once your build folder is setup, you need only follow the instructions below to run the game.

Start the game from the build folder by running:
```
src/run_main
```

## Game Instructions
After running the commands above, you should see a pop-up screen with a game start screen displayed. If you do not see a screen pop up, minimize other windows or check your taskbar for a new icon.

Press the spacebar to start the game and, once the game is running, to jump the bird. The game will end when the bird hits the top/bottom of the window or any pipe surface. After each game the screen will display the high score from all games played in this window. Press the spacebar to play again on the same course. To play a new random course, use the esc key to destroy the window as outlined below and start a new session.

When you are done playing, use the esc key to destroy the pop-up window. Note that destroying the window will erase all data including the high score for this session. To create a new session, follow the instructions in "How to Run" to generate a new game window.
