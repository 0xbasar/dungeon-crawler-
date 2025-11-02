# C-Dungeon-Crawler

A simple, single-file text-based adventure game written entirely in C. This project is designed as a fun, introductory example of game development concepts in a console environment. Navigate a dungeon, fight a monster, find the key, and escape!

 
*(You can replace this with your own screenshot after running the game)*

## Features

-   **Grid-Based Movement:** Navigate a 2D map represented by ASCII characters.
-   **Turn-Based Combat:** Engage in a simple, randomized combat system.
-   **Simple Objective:** Find the key (`K`) to unlock the door (`D`) and reach the exit (`E`).
-   **Cross-Platform:** Uses standard C libraries and a simple system call to clear the screen, making it compatible with Windows, macOS, and Linux.
-   **Minimalist Code:** Everything is contained in a single `main.c` file for easy compilation and understanding.

## Getting Started

To play the game, you will need a C compiler like GCC.

### Prerequisites

-   **GCC Compiler:**
    -   **On Linux:** Usually pre-installed. If not, use your package manager (e.g., `sudo apt-get install build-essential`).
    -   **On macOS:** Install Xcode Command Line Tools by running `xcode-select --install` in your terminal.
    -   **On Windows:** Install [MinGW-w64](https://www.mingw-w64.org/) or use the compiler included with an IDE like Visual Studio.

### How to Compile and Run

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/your-username/c-dungeon-crawler.git
    cd c-dungeon-crawler
    ```

2.  **Compile the C code:**
    Open your terminal or command prompt in the project directory and run the following command:
    ```bash
    gcc main.c -o dungeon_crawler
    ```
    This command compiles `main.c` and creates an executable file named `dungeon_crawler`.

3.  **Run the game:**
    -   On **Linux/macOS**:
        ```bash
        ./dungeon_crawler
        ```
    -   On **Windows**:
        ```bash
        dungeon_crawler.exe
        ```

## How to Play

### Controls

-   `W` - Move Up
-   `A` - Move Left
-   `S` - Move Down
-   `D` - Move Right
-   `Q` - Quit the Game

### Game Elements

-   `@` - You, the player
-   `#` - An impassable wall
-   `.` - An empty floor space
-   `M` - A fearsome monster
-   `K` - The key to the door
-   `D` - The locked door
-   `E` - The exit (you win when you reach it)

### Objective

Your goal is to navigate the dungeon, find the **Key (`K`)**, and use it to unlock the **Door (`D`)**. Once the door is open, you can proceed to the **Exit (`E`)** to win the game. Be careful of the **Monster (`M`)** blocking your path!

## Code Structure

The entire game is in `main.c`. Here's a quick overview of the key functions:

-   `main()`: Contains the main game loop that draws the screen, gets input, and checks for game-over conditions.
-   `initializeGame()`: Sets up the map, player position, and stats at the beginning of the game.
-   `printMap()`: Renders the current state of the game map to the console.
-   `printStatus()`: Displays player health and inventory.
-   `handleInput()`: Reads the player's keyboard input.
-   `movePlayer()`: Contains the logic for movement, collision, and interaction with objects.
-   `fightMonster()`: A self-contained loop for the turn-based combat sequence.
-   `clearScreen()`: A simple cross-platform utility to clear the console.

## License

This project is licensed under the MIT License - see the LICENSE file for details.
