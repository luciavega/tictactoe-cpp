# tictactoe-cpp 

This project is a terminal-based TicTacToe game, developed in C++.

The game is played entirely in the terminal and doesn't use any graphical interface.

It was mainly developed and tested on Windows using PowerShell, but it can be run from any terminal that supports CMake and a C++ compiler.

# how to run the project

The project uses CMake to configure and build the executable.

To run the game:

- Open a terminal in the root folder of the project.

- Configure the project using CMake.
Command: cmake -S . -B build

- Build the project.
Command: cmake --build build

- Run the executable generated in the build folder.
On Windows: build/TicTacToe.exe
On Linux or macOS: ./build/TicTacToe

# game modes

When launching the game, a menu is displayed with two options:

- Two players mode: two human players against each other.
- Player vs AI mode: a human player against the computer.

In player vs AI mode, the player can choose whether they want to start first.

After the game ends, the player is asked if they want to play again.

# code organization

The project is organized as follows:

- src/
Contains the source files of the project:
  - main.cpp: game loop, menu, AI logic and game rules.
  - Player.cpp: player creation and input handling.

- include/
Contains the header files:
  - Player.hpp: player structure and function declarations.

- CMakeLists.txt
Configuration file used by CMake to build the project.

- README.md
Project documentation.

The build directory is intentionally excluded from version control using a .gitignore file, as it contains generated files.

# ai implementation

The AI uses a simple decision strategy:

- If it can win in one move, it does so.

- If the opponent can win in the next move, it blocks that move.

- Otherwise, it prioritizes the center, then corners, then the remaining free cells.

This approach makes the AI more challenging than a purely random strategy.

# additional features

Here is a list of the improvements that were added beyond the base requirements:

- Input validation for player names, symbols and moves.

- Symbol selection restricted to X or O.

- Replay option after each game.

- Option for the player to choose who starts in Player vs AI mode.

- Improved AI logic with blocking and winning behavior.

# problems encountered and solutions

While developing the project, some problems appeared:

- Invalid user input could cause errors or unexpected behavior.

- Players or the AI could try to play in already occupied cells.

- The AI did not always block the opponent's winning moves.

- Build files were accidentally tracked by Git.

These problems were fixed by adding proper input validation, checking board state before each move, improving the AI logic, and using a .gitignore file to exclude generated build files.

# conclusion

This project was an opportunity to apply basic C++ concepts in a small but complete program.

It covers user input handling, simple game logic, and basic AI behavior, while also following a clear project structure and using CMake and Git for compilation and version control.

The result is a functional terminal-based game that meets the project requirements.