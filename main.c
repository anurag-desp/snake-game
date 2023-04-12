#include <stdio.h>
#include "mysnake.h"
#include "snake.h"
#include "myfruit.h"
#include "fruit.h"

int main(int argc, char** argv){
    Snake* snake = createSnake();
    int score = 0;
    int last_score = 0;
    int fruit_eaten;
    
    Fruit fruit;
    fruit = setFruit();

    clearScreen();
    
    char hit = 'd';
    gameArea(snake, fruit, hit, &score);
    int sleep_time = 200000;
    while(1){
        clearScreen();
        drawLogo();
        usleep(1000);

        if(game_over){
            snake = gameOver(&score, snake);
            fruit = setFruit();
            hit = 'd';
            sleep_time = 200000;
            usleep(10000);
        }

        fruit_eaten = gameArea(snake, fruit, hit, &score);
        
        if(fruit_eaten){
            fruit = setFruit();
            snake = addBody(snake, hit);
        }

        if(kbhit()){
            hit = getchar();
            printf("HIT!\n");
        }
        snake = moveSnake(snake, hit);
        
        if(score >= last_score){
            if(sleep_time > 50000)
                sleep_time -= 500;
            usleep(sleep_time);
            last_score = score;
        }
    }
    return 0;
}