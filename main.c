// ============================================================================
// A Simple C Text-Based Adventure Game: "C-Dungeon Crawler"
// Author: Your GitHub Name
// License: MIT
// Description: A minimal dungeon crawler where you find a key to escape.
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <time.h> // For seeding the random number generator

// -- Game Configuration --
#define MAP_ROWS 10
#define MAP_COLS 20

// Player starting stats
#define PLAYER_START_HEALTH 100
#define PLAYER_ATTACK_MIN 5
#define PLAYER_ATTACK_MAX 15

// Monster starting stats
#define MONSTER_START_HEALTH 50
#define MONSTER_ATTACK_MIN 3
#define MONSTER_ATTACK_MAX 10

// -- Map Symbols --
#define PLAYER '@'
#define MONSTER 'M'
#define WALL '#'
#define FLOOR '.'
#define KEY 'K'
#define DOOR 'D'
#define EXIT 'E'

// -- Global Game State --
char map[MAP_ROWS][MAP_COLS];
int playerX, playerY;
int playerHealth;
int monsterHealth;
int hasKey = 0;      // 0 for false, 1 for true
int monsterIsAlive = 1; // 1 for true, 0 for false

// -- Function Prototypes --
void initializeGame();
void printMap();
void printStatus();
void handleInput();
void movePlayer(int dx, int dy);
void fightMonster();
void clearScreen();
int getRandom(int min, int max);

// ============================================================================
// MAIN GAME LOOP
// ============================================================================
int main() {
    // Seed the random number generator
    srand(time(NULL));

    initializeGame();

    // Game loop
    while (1) {
        clearScreen();
        printf("=== C-Dungeon Crawler ===\n");
        printMap();
        printStatus();
        handleInput();

        // Check for game over condition
        if (playerHealth <= 0) {
            clearScreen();
            printMap();
            printf("\n--- GAME OVER ---\nYou were defeated by the monster!\n");
            break; // Exit game loop
        }
    }

    return 0;
}

// ============================================================================
// GAME FUNCTIONS
// ============================================================================

/**
 * @brief Sets up the initial state of the game: map, player, items, etc.
 */
void initializeGame() {
    playerHealth = PLAYER_START_HEALTH;
    monsterHealth = MONSTER_START_HEALTH;

    // Create the map layout
    const char initialMap[MAP_ROWS][MAP_COLS + 1] = {
        "####################",
        "#@........#........#",
        "#.###.###.#.######.#",
        "#...#.#...#.#......#",
        "#.###.#.#####.####.#",
        "#.#...#...#...#K.#.#",
        "#.#######.###.##.#.#",
        "#.#.......#M..#..#D#",
        "#.........#...#..#.#",
        "####################"
    };

    // Find player start and copy map
    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLS; x++) {
            map[y][x] = initialMap[y][x];
            if (map[y][x] == PLAYER) {
                playerX = x;
                playerY = y;
            }
            if (map[y][x] == DOOR) {
                // The exit is behind the door
                 map[y][MAP_COLS-1] = EXIT;
            }
        }
    }
}

/**
 * @brief Prints the current state of the map to the console.
 */
void printMap() {
    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLS; x++) {
            printf("%c", map[y][x]);
        }
        printf("\n");
    }
}

/**
 * @brief Prints the player's status (health, inventory).
 */
void printStatus() {
    printf("\nHealth: %d\n", playerHealth);
    printf("Inventory: ");
    if (hasKey) {
        printf("Key\n");
    } else {
        printf("Empty\n");
    }
    printf("------------------------\n");
    printf("Controls: W(up), A(left), S(down), D(right), Q(quit)\n");
    printf("Enter your move: ");
}

/**
 * @brief Handles user input and calls the appropriate action.
 */
void handleInput() {
    char input;
    // The space before %c consumes any leading whitespace, including the newline
    scanf(" %c", &input);

    switch (input) {
        case 'w':
        case 'W':
            movePlayer(0, -1);
            break;
        case 'a':
        case 'A':
            movePlayer(-1, 0);
            break;
        case 's':
        case 'S':
            movePlayer(0, 1);
            break;
        case 'd':
        case 'D':
            movePlayer(1, 0);
            break;
        case 'q':
        case 'Q':
            printf("Quitting the game. Farewell!\n");
            exit(0);
        default:
            // Invalid input, the loop will just restart
            break;
    }
}

/**
 * @brief Logic for moving the player and handling collisions/interactions.
 * @param dx The change in the x-coordinate.
 * @param dy The change in the y-coordinate.
 */
void movePlayer(int dx, int dy) {
    int newX = playerX + dx;
    int newY = playerY + dy;

    // Check what the player is trying to move into
    char destination = map[newY][newX];

    switch (destination) {
        case WALL:
            // Can't move into a wall
            break;
        case MONSTER:
            if(monsterIsAlive) {
                fightMonster();
            } else {
                // If monster is dead, treat as floor
                map[playerY][playerX] = FLOOR;
                playerX = newX;
                playerY = newY;
                map[playerY][playerX] = PLAYER;
            }
            break;
        case KEY:
            hasKey = 1;
            // Treat as floor after picking up
            map[playerY][playerX] = FLOOR;
            playerX = newX;
            playerY = newY;
            map[playerY][playerX] = PLAYER;
            break;
        case DOOR:
            if (hasKey) {
                // Open the door (now it's floor) and move onto it
                map[newY][newX] = FLOOR;
                map[playerY][playerX] = FLOOR;
                playerX = newX;
                playerY = newY;
                map[playerY][playerX] = PLAYER;
            } else {
                // Door is locked
            }
            break;
        case EXIT:
            clearScreen();
            printMap();
            printf("\n*** CONGRATULATIONS! ***\nYou found the exit and escaped the dungeon!\n");
            exit(0);
        case FLOOR:
        default:
            // Move the player
            map[playerY][playerX] = FLOOR;
            playerX = newX;
            playerY = newY;
            map[playerY][playerX] = PLAYER;
            break;
    }
}

/**
 * @brief Manages the turn-based combat between the player and the monster.
 */
void fightMonster() {
    clearScreen();
    printf("--- COMBAT! ---\nAn angry monster blocks your path!\n\n");

    while(playerHealth > 0 && monsterHealth > 0) {
        // Player's turn
        int playerDamage = getRandom(PLAYER_ATTACK_MIN, PLAYER_ATTACK_MAX);
        monsterHealth -= playerDamage;
        printf("You attack the monster for %d damage. Monster health: %d\n", playerDamage, monsterHealth > 0 ? monsterHealth : 0);

        if (monsterHealth <= 0) break;

        // Monster's turn
        int monsterDamage = getRandom(MONSTER_ATTACK_MIN, MONSTER_ATTACK_MAX);
        playerHealth -= monsterDamage;
        printf("The monster attacks you for %d damage. Your health: %d\n\n", monsterDamage, playerHealth > 0 ? playerHealth : 0);

        // A small delay to make combat readable
        printf("Press Enter to continue...");
        while (getchar() != '\n'); // Clear input buffer
        getchar(); // Wait for Enter
    }

    if (monsterHealth <= 0) {
        printf("\nYou defeated the monster!\n");
        monsterIsAlive = 0;
        // Find and remove monster from map
         for (int y = 0; y < MAP_ROWS; y++) {
            for (int x = 0; x < MAP_COLS; x++) {
                if(map[y][x] == MONSTER) {
                    map[y][x] = FLOOR;
                }
            }
        }
    }
    // If player health is <= 0, the main loop will handle the game over
    
    printf("\nPress Enter to return to the dungeon...");
    getchar();
}


// -- Utility Functions --

/**
 * @brief A cross-platform way to clear the console screen.
 */
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    // Assume POSIX
    system("clear");
#endif
}

/**
 * @brief Generates a random number within a specified range (inclusive).
 */
int getRandom(int min, int max) {
    return min + rand() % (max - min + 1);
}
