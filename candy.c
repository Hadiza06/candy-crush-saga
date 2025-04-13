#include "crush.h"


/// Function to clear the screen (portable for Mac/Linux)
void clearScreen() {
    printf("\033[H\033[J");
}

/// Function to save the player's score to a file
void saveScore(int totalScore,char playerName[50]) {
     /// Store player name
    FILE *file = fopen("scoreJoueur.txt", "a");
    if (file == NULL) {
        printf("Error: Could not save the score.\n");
        return;
    }
    fprintf(file, "Player: %s\nTotal Score: %d\n", playerName, totalScore);
    fclose(file);
    printf("Your score has been saved to scoreJoueur.txt.\n");
}
void Color(int couleurDuTexte, int couleurDeFond) {
    printf("\033[%d;%dm", couleurDuTexte + 30, couleurDeFond + 40);
}

void mainMenu(char playerName[50]) {
     /// Store player name
    int choice;
    int totalScore = 0; /// Total score across all games

    do {
        clearScreen();
        printf("\033[1;31m==== CandyECE Main Menu ====\033[0m\n"); /// Red
        printf("Welcome, %s!\n", playerName);
        printf("1. Play Game\n2. Game Rules\n3. Credits\n4. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                levelMenu(&totalScore);
                break;
            case 2:
                clearScreen();
                printf("Game Rules:\n- Match 3 or more candies to score points.\n- Complete the objectives to win.\nPress 'L' to launch the game.");
                printf("Press any key to return to the main menu...");
                getchar();
                getchar();
                break;
            case 3:
                clearScreen();
                printf("Credits:\nDeveloped by:\n Minh Tri\nDjeneba Coulibaly\nHadiza Hamidou Ba...\n");
                printf("\nPress any key to return to the main menu...");
                getchar();
                getchar();
                break;
            case 4:
                printf("Goodbye, %s! Your total score is %d.\n", playerName, totalScore);
                saveScore(totalScore, playerName);
                exit(0);
                break;
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    } while (choice != 4);
}

void levelMenu(int *totalScore) {
    char playerName[50]; /// Store player name
    int level;
    do {
        clearScreen();
        printf("\033[1;34m==== Level Menu ====\033[0m\n"); /// blue
        printf("1. Level 1\n2. Level 2\n3. Level 3\n4. Level 4\n5. Return to Main Menu\n");
        printf("\nEnter your choice: ");
        if (scanf("%d", &level) != 1 || level < 1 || level > 5) {
            printf("\nInvalid choice. Try again.\n");
            while (getchar() != '\n'); /// Clear input
            continue;
        }

        if (level == 5) return; /// return menu
        startGame(level, totalScore, playerName); /// Pass level to startGame
    } while (1);
}





void startGame(int level, int *totalScore,char playerName[50]) {
    char playername[50]; /// Store player name
    char grid[GRID_SIZE][GRID_SIZE];
    int score = 0;
    char launch;
    time_t startTime, currentTime;

    printf("You selected Level %d\n", level);
    printf("Press '\033[1;32mL\033[0m' to launch the game or '\033[1;31mA\033[0m' to abandon: ");
    scanf(" %c", &launch);

    if (launch == 'A' || launch == 'a') {
        printf("\nGame abandoned. Returning to level menu...\n");
        return;
    } else if (launch != 'L' && launch != 'l') {
        printf("\nInvalid input. Returning to level menu...\n");
        return;
    }

    initializeGrid(grid, level);

    int exitGame = 0;
    time(&startTime);

    while (!exitGame) {
        time(&currentTime);
        int remainingTime = GAME_TIME_LIMIT - (int)difftime(currentTime, startTime);

        if (remainingTime <= 0) {
            printf("\033[1;31m\nTime's up! Your game has ended.\033[0m\n");
            *totalScore += score;
            break;
        }

        clearScreen();
        printf("\nPlayer: %s | Level: %d | \033[1;32mScore: %d | Time Left: %d seconds\033[0m\n",
               playername, level, score, remainingTime);
        displayGrid(grid);

        printf("\nEnter row (1-15) and column (A-O) to select candy (or type '0' to quit): ");
        int row;
        char col;

        if (scanf(" %d %c", &row, &col) != 2) {
            printf("\nInvalid input. Try again.\n");
            while (getchar() != '\n');
            continue;
        }

        if (row == 0) {
            printf("Exiting game...\n");
            exitGame = 1;
            break;
        }

        int colIndex = col - 'A';
        if (row < 1 || row > GRID_SIZE || colIndex < 0 || colIndex >= GRID_SIZE) {
            printf("Invalid position. Try again.\n");
            continue;
        }

        calculateScore(grid, row - 1, colIndex, &score);
        if (level >= 4) {
            updateGrid(grid);
        }


        if (score >= 50) {
            printf("\033[1;32m\nCongratulations! You reached 50 points!\033[0m\n");
            *totalScore += score;

            printf("\nPress Enter to return to the level menu...\n");
        while (getchar() != '\n');
            getchar();
            break;
}

    }

    printf("Your score for this game: %d\n", score);
    printf("Returning to level menu...\n");
    while (getchar() != '\n');
}



void displayGrid(char grid[GRID_SIZE][GRID_SIZE]) {
    int i,j;
    /// Print column headers
    printf("    "); /// Space to align column headers
    for (char c = 'A'; c < 'A' + GRID_SIZE; c++) {
        printf("  %c   ", c); /// Print column headers with wide spacing
    }
    printf("\n");

    /// Print first horizontal line
    printf("   +");
    for ( i = 0; i < GRID_SIZE; i++) {
        printf("-----+");
    }
    printf("\n");

    /// Print rows of data
    for ( i = 0; i < GRID_SIZE; i++) {
        printf("%2d |", i + 1); /// Print row numbers with alignment
        for ( j = 0; j < GRID_SIZE; j++) {
            /// Set color for each character type
            switch (grid[i][j]) {
                case 'C': printf("\033[1;31m"); break; /// red
                case 'F': printf("\033[1;32m"); break; /// green
                case 'R': printf("\033[1;33m"); break; /// yellow
                case 'S': printf("\033[1;34m"); break; ///blue
                case 'T': printf("\033[1;35m"); break; /// purple
                case 'J': printf("\033[1;36m"); break; /// light blue
                case 'X': printf("\033[1;30m"); break; /// grey
                default: printf("\033[1;37m"); break;  /// white
            }
            printf("  %c  ", grid[i][j]); /// Print characters in cell
            printf("\033[0m"); /// Reset color immediately after printing characters
            printf("|");
        }
        printf("\n");

        /// Print horizontal lines after each row
        printf("   +");
        for ( j = 0; j < GRID_SIZE; j++) {
            printf("-----+");
        }
        printf("\n");
    }
}




void initializeGrid(char grid[GRID_SIZE][GRID_SIZE], int level) {
    int i,j;
    srand(time(NULL));
    const char candies[NUM_TYPES] = {'C', 'F', 'R', 'S', 'T'};

    /// Initialize the mesh as empty
    for ( i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = ' '; /// Initialize empty cell
        }
    }

    /// Fill random candies into the grid
    for ( i = 0; i < GRID_SIZE; i++) {
        for ( j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == ' ') {
                grid[i][j] = candies[rand() % NUM_TYPES];
            }
        }
    }

    /// Add obstacles for level >= 2
    if (level >= 2) {
        placeObstacles(grid);
    }

    /// Add Joker candy for level 3 or 4
    if (level == 3 || level == 4) {
        for (int i = 0; i < MAX_JOKERS; i++) {
            int row, col;
            do {
                row = rand() % GRID_SIZE;
                col = rand() % GRID_SIZE;
            } while (grid[row][col] == 'X' || grid[row][col] == 'J');
            grid[row][col] = 'J'; /// Add Joker Candy
        }
    }
}


void placeObstacles(char grid[GRID_SIZE][GRID_SIZE]) {
    int i;
    int numObstacles = (GRID_SIZE * GRID_SIZE * OBSTACLE_PERCENTAGE) / 100;

    for ( i = 0; i < numObstacles; i++) {
        int row, col;
        do {
            row = rand() % GRID_SIZE;
            col = rand() % GRID_SIZE;
        } while (grid[row][col] != ' ' && grid[row][col] != 'C' && grid[row][col] != 'F');

        grid[row][col] = 'X';
    }
}


void applyCascade(char grid[GRID_SIZE][GRID_SIZE]) {
    int col,row,r;
    for ( col = 0; col < GRID_SIZE; col++) {
        for ( row = GRID_SIZE - 1; row > 0; row--) {
            if (grid[row][col] == ' ') {
                for ( r = row; r > 0; r--) {
                    grid[r][col] = grid[r - 1][col];
                }
                grid[0][col] = ' ';
            }
        }
    }
}



void fillEmptySpaces(char grid[GRID_SIZE][GRID_SIZE]) {
    int col,row;
    const char candies[NUM_TYPES] = {'C', 'F', 'R', 'S', 'T'};
    for ( col = 0; col < GRID_SIZE; col++) {
        for ( row = 0; row < GRID_SIZE; row++) {
            if (grid[row][col] == ' ') { /// If the cell is blank
                grid[row][col] = candies[rand() % NUM_TYPES]; /// Fill in new random candy
            }
        }
    }
}

void updateGrid(char grid[GRID_SIZE][GRID_SIZE]) {
    int cascade,col,row;
    do {
        cascade = 0;
        for ( col = 0; col < GRID_SIZE; col++) {
            for (row = GRID_SIZE - 1; row > 0; row--) {
                if (grid[row][col] == ' ' && grid[row - 1][col] != ' ') {
                    grid[row][col] = grid[row - 1][col];
                    grid[row - 1][col] = ' ';
                    cascade = 1;
                }
            }
        }
    } while (cascade);

    fillEmptySpaces(grid);
}



int calculateStraightLineScore(char grid[GRID_SIZE][GRID_SIZE], int row, int col, char candyType) {
    int count,score,left,right;
    count = 1;
     score = 0;

    /// Check horizontal (left and right)
     left = col - 1;
     right = col + 1;
    while (left >= 0 && grid[row][left] == candyType) {
        count++;
        left--;
    }
    while (right < GRID_SIZE && grid[row][right] == candyType) {
        count++;
        right++;
    }
    if (count >= 3) { /// If there are at least 3 candies
        for (int i = left + 1; i < right; i++) {
            grid[row][i] = ' '; /// Clear the candies
        }
        score += count;
    }

    /// Check vertical (top and bottom)
    count = 1;
    int up = row - 1, down = row + 1;
    while (up >= 0 && grid[up][col] == candyType) {
        count++;
        up--;
    }
    while (down < GRID_SIZE && grid[down][col] == candyType) {
        count++;
        down++;
    }
    if (count >= 3) { /// If there are at least 3 candies
        for (int i = up + 1; i < down; i++) {
            grid[i][col] = ' '; /// Clear candy
        }
        score += count;
    }

    return score;
}


void calculateScore(char grid[GRID_SIZE][GRID_SIZE], int row, int col, int *score) {
     int candyScore,clearedCandies, totalScore;
     char candy;
    candy = grid[row][col];
    if (candy == ' ' || candy == 'X') {
        printf("\nThis candy is either matched or an obstacle.\n");
        return;
    }

    candyScore = 0;
    switch (candy) {
        case 'C': candyScore = 1; break;
        case 'F': candyScore = 2; break;
        case 'R': candyScore = 3; break;
        case 'S': candyScore = 4; break;
        case 'T': candyScore = 5; break;
        case 'J': candyScore = 10; break; /// Joker candy
        default: break;
    }

     clearedCandies = calculateStraightLineScore(grid, row, col, candy);
    if (clearedCandies >= 3) {
        totalScore = candyScore * clearedCandies;
        *score += totalScore;
        printf("\nYou cleared %d candies worth %d points!\n", clearedCandies, totalScore);
    } else {
        printf("\nNot enough candies to clear.\n");
    }
}
