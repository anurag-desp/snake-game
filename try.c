#include <stdio.h>
#include <stdlib.h>

typedef struct snake{
    int x_pos;
    int y_pos;
    char shape;
    struct snake* next;
} Snake;


// snakes tail will be lists's head and vice versa
void display(Snake* head){
    Snake* temp = head;
    while(temp != NULL){
        printf("%c", temp -> shape);
        temp = temp -> next;
    }
    printf("\n");    
}

Snake* createSnake(){
    Snake* snake_tail = malloc(sizeof(Snake));
    snake_tail -> shape = '<';
    snake_tail -> next = NULL;

    Snake* snake_body1 = malloc(sizeof(Snake));
    snake_body1 -> shape = '~';
    snake_body1 -> next = NULL;

    Snake* snake_body2 = malloc(sizeof(Snake));
    snake_body2 -> shape = '~';
    snake_body2 -> next = NULL;

    Snake* snake_head = malloc(sizeof(Snake));
    snake_head -> shape = 'o';
    snake_head -> next = NULL;

    // assembling body parts
    snake_tail -> next = snake_body1;
    snake_body1 -> next = snake_body2;
    snake_body2 -> next = snake_head;

    return snake_tail;
}

Snake* insertSnakeBody(Snake* snake_tail){
    Snake* new_part = malloc(sizeof(Snake));

    new_part -> shape = '~';
    
    Snake* temp = snake_tail -> next;
    snake_tail -> next = new_part;
    new_part -> next = temp;

    return snake_tail;
}
int main(void){
    Snake* snake_tail = createSnake();
    display(snake_tail);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
    snake_tail = insertSnakeBody(snake_tail);
    display(snake_tail);
    snake_tail = insertSnakeBody(snake_tail);
    display(snake_tail);
    snake_tail = insertSnakeBody(snake_tail);
    display(snake_tail);
    snake_tail = insertSnakeBody(snake_tail);
    display(snake_tail);

    
    return 0;
}