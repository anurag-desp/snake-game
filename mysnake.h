#pragma once

#include "myfruit.h"

#define clearScreen() printf("\033[H\033[J");
#define HEIGHT 25
#define WIDTH 50
int game_over = 0;
int heighest_score = 0;
// typedef enum direction{LEFT, RIGHT, UP, DOWN} Dir; // Wanted to use but didn't end up using it :)
// SNAKE
typedef struct snake{
    char part;
    int x_position;
    int y_position;
    struct snake* next;
} Snake;

Snake* createSnake();   // Instantiates the snake with 5 bodyparts
Snake* addBody(Snake* head, char hit); // To added a new body pwrt if the snakes eats the fruits
Snake* moveSnake(Snake* head, char hit);    // Animate the snake movements based on the keybord hit
void drawArea(char area[HEIGHT][WIDTH], int score); // Draw the playing area on the terminal
int gameArea(Snake* head, Fruit fruit, char hit, int* score);    // Set the appropriate symbols to be drawn on a 2d array
void popTail(Snake* head);
Snake* pushPart(Snake* head, Snake* part_to_push);
int correctHit(char hit); // wheter the kbhit by user was the accepted hits(a, s, w, d) or something else

void drawLogo();
Snake* drawGameover(int* score, Snake* snake);
int snakeEatsItself(Snake* head);
void destroySnake(Snake** snake);