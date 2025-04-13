#ifndef CRUSH_H_INCLUDED
#define CRUSH_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "crush.h"
#define GRID_SIZE 15
#define NUM_TYPES 5
#define OBSTACLE_PERCENTAGE 10
#define MAX_JOKERS 10

#define GAME_TIME_LIMIT 120

// Function declarations
void mainMenu(char playerName[50]);
void levelMenu();
void startGame(int level, int *totalScore,char playerName[50]);
void displayGrid(char grid[15][15]);
void initializeGrid(char grid[GRID_SIZE][GRID_SIZE], int level);
void calculateScore(char grid[GRID_SIZE][GRID_SIZE], int row, int col, int *score);
void clearScreen();
void calculateScore(char grid[GRID_SIZE][GRID_SIZE], int row, int col, int *score);
void fillEmptySpaces(char grid[GRID_SIZE][GRID_SIZE]);
void placeObstacles(char grid[GRID_SIZE][GRID_SIZE]);
void applyCascade(char grid[GRID_SIZE][GRID_SIZE]);
void saveScore(int totalScore,char playerName[50]);
void Color(int couleurDuTexte, int couleurDeFond);
void updateGrid(char grid[GRID_SIZE][GRID_SIZE]);
int calculateStraightLineScore(char grid[15][15], int row, int col, char candyType);




#endif // CRUSH_H_INCLUDED
