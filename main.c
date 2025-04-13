#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "crush.h"
#define GRID_SIZE 15
#define NUM_TYPES 5
#define OBSTACLE_PERCENTAGgcc 10
#define MAX_JOKERS 10

#define GAME_TIME_LIMIT 120

/// Main function
int main() {
    char playerName[50]; /// Store player name
    clearScreen();
    printf("Enter your name: ");
    fgets(playerName, sizeof(playerName), stdin);
    playerName[strcspn(playerName, "\n")] = 0; /// Remove newline character
    mainMenu( playerName);
    return 0;
}
