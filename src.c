#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h> // for sleep and getch

// box dimensions
#define height 25
#define width 50

#define clearScreen() printf("\033[H\033[J");

int getch(void)
{
	struct termios oldt, newt;
	int ch;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	return ch;
}

typedef struct snake{
    int x_position;
    int y_position;
    int shape;
    struct snake* next;
} Snake;

typedef struct{
    int x_position;
    int y_position;
} Fruit;

int game_over = 0;  // 0: game NOT over. 1: game over
int heighest_score = 0;

void gameOver(int* score, Snake* snake){
        clearScreen();

        // game over logo
        printf("\t\t\t.__________________________________________________________________________________________.\n");
        printf("\t\t\t|                                                                                          |\n");
        printf("\t\t\t|\tG\tA\tM\tE\t\tO\tV\tE\tR\t!\t   |\n");
        printf("\t\t\t|__________________________________________________________________________________________|\n");

        printf("\tYour Score: %d\n", *score);
        if(heighest_score < *score) heighest_score = *score;
        printf("\tHeighest Score: %d\n", heighest_score);


        printf("\n\t\tpress any key to RETRY or q to QUIT: ");
        char key = getch();
        if(key == 'q' || key == 'Q') exit(0);
        *score = 0;
}

Fruit putFruit(){
    Fruit fruit;
    fruit.x_position = rand()%(width-1);
    fruit.y_position = rand()%(height-1);

    // we might get either of them at 0, that would place the fruit on the border
    while(fruit.x_position == 0) fruit.x_position = rand()%width;
    while(fruit.y_position == 0) fruit.y_position = rand()%height;

    return fruit;
}

void snakeShape(int shapes){
    switch(shapes){
        case 1:
            printf("~:");
            break;
        case 2:
            printf(":~");
            break;
        case 3:
            printf("!");
            break;
        case 4:
            printf("i");
            break;
    }
}

Fruit drawArea(Fruit fruit, Snake snake){
    // clearScreen();
    static int score = 0;

    for(int i = 0; i < height; i++){
        if(i != 0)
            printf("|");
        else printf(" ");

        for(int j = 0; j < width; j++){
            if(i == 0 || i == height-1){
                printf("_");
                continue;
            }

            if(i == fruit.y_position && j == fruit.x_position){
                if(i == snake.y_position && j == snake.x_position){
                    snakeShape(snake.shape);
                    fruit = putFruit();
                    score += 10;
                }
                else printf("*");
                continue;  
            }

            if(i == snake.y_position && j == snake.x_position){
                snakeShape(snake.shape);
                continue;
            }

            printf(" ");
        }

        if(i != 0)
            printf("|\n");
        else printf("\n");
    }
    if(snake.y_position <= 0 || snake.y_position >= height-1 || snake.x_position <= 0 || snake.x_position >= width-1){
        game_over = 1;
        gameOver(&score, &snake);
        return fruit;
    }

    printf("\t\t Score: %d\n", score);
    if(heighest_score < score) heighest_score = score;
    printf("\t\t Heighest Score: %d\n", heighest_score);

    return fruit;
}
 
Snake input(Snake snake){
    static int snake_x_position = 1;
    static int snake_y_position = 1;
    
    if(game_over == 1){
        snake_x_position = 1;
        snake_y_position = 1;
        game_over = 0;
    }

    char user_direction;
    // scanf("%c", &user_direction); // getch, getchar, getc not working
    user_direction = getch();
    switch (user_direction)
    {
        case 'w':
            snake_y_position--;
            snake.shape = 4;
            break;
        case 's':
            snake_y_position++;
            snake.shape = 3;
            break;
        case 'd':
            snake_x_position++;
            snake.shape = 1;
            break;
        case 'a':
            snake_x_position--;
            snake.shape = 2;
            break;
    }

    snake.y_position = snake_y_position;
    snake.x_position = snake_x_position;


    return snake;
}

void drawLogo(){
    printf("\t\t\t ._________________________________________________________________________.\n");
    printf("\t\t\t |                                                                         |\n");
    printf("\t\t\t | S\tN\tA\tK\tE\t\tG\tA\tM\tE  |\n");
    printf("\t\t\t |_________________________________________________________________________|\n\n\n");
}

int main(void){

    Fruit fruit;
    Snake snake;
    snake.x_position = 1;
    snake.y_position = 1;
    snake.shape = 1;    // snake.shape(1: '~:', 2: ':~', 3: '!', 4: 'i')

    fruit = putFruit();
    clearScreen();

    while(1)
    {
        drawLogo();
        fruit = drawArea(fruit, snake);
        snake = input(snake);
        clearScreen();
        sleep(0.2);
    }

    return 0;
}