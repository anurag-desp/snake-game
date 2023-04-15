#pragma once

#include <stdio.h>
#include <stdlib.h> // memory allocation
#include <unistd.h> // for sleep
#include "kbhit.h"
#include "mysnake.h"
#include "myfruit.h"
#include "fruit.h"

Snake* createSnake(){
    Snake* head = malloc(sizeof(Snake));
    head -> part = '@'; 
    head -> x_position = 5;
    head -> y_position = 1;
    head -> next = NULL;
    
    // insert in the beginning
    int body_size = 4;
    Snake* temp = head;
    while(body_size >= 1){
        Snake* new_part = malloc(sizeof(Snake));
        temp -> next = new_part;
        new_part -> part = '0';
        new_part -> x_position = body_size--;
        new_part -> y_position = 1;
        temp = new_part;
    }

    return head;
}

int correctHit(char hit){
    if(
        hit == 'a' ||
        hit == 's' ||
        hit == 'w' ||
        hit == 'd'
    ) return 1;
    
    return 0;
}

int complementHit(char last_hit, char hit){
    if(last_hit == 'a' && hit == 'd'){
        return 1;
    }

    if(last_hit == 'd' && hit == 'a'){
        return 1;
    }

    if(last_hit == 'w' && hit == 's'){
        return 1;
    }

    if(last_hit == 's' && hit == 'w'){
        return 1;
    }

    return 0;
}

Snake* addBody(Snake* head, char hit){
    static int last_hit = 'd'; // in case someone hits something other than 'a, s, w, d'
    Snake* new_part = malloc(sizeof(Snake));
    if(new_part == NULL){
        printf("Error occured while allocating memory!\n\n");
        return NULL;
    }

    new_part -> part = '@';

    // putting in the correct coordinates
    if(
        !correctHit(hit) ||
        complementHit(last_hit, hit)
    ) hit = last_hit;

    
    switch(hit){
        // Left
        case 'a':
            new_part -> x_position = head -> x_position - 1;
            new_part -> y_position = head -> y_position;
            break;

        // Right
        case 'd':
            new_part -> x_position = head -> x_position + 1;
            new_part -> y_position = head -> y_position;
            break;
        
        // Up
        case 'w':
            new_part -> x_position = head -> x_position;
            new_part -> y_position = head -> y_position - 1;
            break;
        
        case 's':
            new_part -> x_position = head -> x_position;
            new_part -> y_position = head -> y_position + 1;
            break;

        default:
            break;
    }
    head -> part = '0';
    new_part -> next = head;
    head = new_part;

    last_hit = hit;
    return head;
}

void popTail(Snake* head){
    Snake* temp = head;
    Snake* pre = NULL;
    while(temp -> next){
        pre = temp;
        temp = temp -> next;
    }
    pre -> next = NULL;
    free(temp);
}

Snake* pushPart(Snake* head, Snake* part_to_push){
    part_to_push -> next = head;
    head = part_to_push;
}

Snake* moveSnake(Snake* head, char hit){
    popTail(head);
    head = addBody(head, hit);
    return head;
}



int snakeEatsItself(Snake* head){
    Snake* temp = head -> next;
    while(temp){
        if(
            temp -> x_position == head -> x_position &&
            temp -> y_position == head -> y_position
        ) return 1;
        
        temp = temp -> next;
    }
    return 0;
}

void drawArea(char area[HEIGHT][WIDTH], int score){  
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            printf("%c", area[i][j]);
        }
        printf("\n");
    }
    printf("\t\t Score: %d\n", score);
    if(heighest_score < score){
        heighest_score = score;
    }
    printf("\t\t Heighest Score: %d\n\n", heighest_score);
}

int gameArea(Snake* head, Fruit fruit, char hit, int* score){
    char area[HEIGHT][WIDTH];
    Snake* temp = head;
    int flag = 0;   // if snake part: 1, if space: 0;
    int fruit_eaten = 0;

    for(int i = 0; i < HEIGHT; i++){
        // FIRST LINE
        if(i == 0){
            area[i][0] = '.';
            area[i][WIDTH-1] = '.';
            for(int j = 1; j < WIDTH-1; j++){
                area[i][j] = '_';
            }
            continue;
        }

        // LAST LINE
        if(i == HEIGHT-1){
            area[i][0] = '|';
            area[i][WIDTH-1] = '|';
            for(int j = 1; j < WIDTH-1; j++){
                area[i][j] = '_';
            }
            continue;
        }

        if(
            head -> y_position == 0 ||
            head -> y_position == HEIGHT -1
        ){
            game_over = 1;
        }

        // MIDDLE AREA
        for(int j = 0; j < WIDTH; j++){
            flag = 0; // reset
            temp = head; // reset
            
            if(fruit.x_position == j && fruit.y_position == i){
                if(head -> x_position == fruit.x_position && head -> y_position == fruit.y_position){
                    area[i][j] = head -> part; // @: head of the snake;
                    fruit_eaten = 1;
                    *score += 10;
                }
                else
                    area[i][j] = fruit.shape;
                
                continue;
            }

            if(j == 0 || j == WIDTH-1){
                area[i][j] = '|';
                continue;
            }

            if(
                head -> x_position == 0 ||
                head -> x_position == WIDTH -1
            ){
                game_over = 1;
            }

            while(temp){
                if(temp -> x_position == j && temp -> y_position == i){
                    area[i][j] = temp -> part;
                    flag = 1;
                    break;
                }
                temp = temp -> next;
            }
            if(!flag){
                area[i][j] = ' ';
            }

            if(snakeEatsItself(head)){
                game_over = 1;
            }
        }
    }
    drawArea(area, *score);
    return fruit_eaten;
}

// NOT Used
void destroySnake(Snake** snake)
{  
  Snake* current = *snake;
  Snake* next;
  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
  *snake = NULL;
}

void drawLogo(){
    printf("\t\t\t ._________________________________________________________________________.\n");
    printf("\t\t\t |                                                                         |\n");
    printf("\t\t\t | S\tN\tA\tK\tE\t\tG\tA\tM\tE  |\n");
    printf("\t\t\t |_________________________________________________________________________|\n\n\n");
}

Snake* gameOver(int* score, Snake* snake){
    clearScreen();

    // game over logo
    printf("\t\t\t.__________________________________________________________________________________________.\n");
    printf("\t\t\t|                                                                                          |\n");
    printf("\t\t\t|\tG\tA\tM\tE\t\tO\tV\tE\tR\t!\t   |\n");
    printf("\t\t\t|__________________________________________________________________________________________|\n");

    printf("\tYour Score: %d\n", *score);
    printf("\tHeighest Score: %d\n", heighest_score);


    printf("\n\t\tpress any key to RETRY or q to QUIT: ");
    char key = getchar();
    if(key == 'q' || key == 'Q'){
        destroySnake(&snake);
        if(!snake)
            printf("Snake Destroyed!\n");
        else
            printf("The Snake Lives!\n");
        
        exit(0);
    }
    
    game_over = 0;
    *score = 0;
    destroySnake(&snake); // I don't know why this is causing problem in gameArea() upon retry!
    snake = createSnake();
    return snake;
}