#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "myfruit.h"
#include "mysnake.h"


Fruit setFruit(){
    Fruit fruit;
    srand(time(NULL));
    fruit.x_position = rand()%(WIDTH-1);
    fruit.y_position = rand()%(HEIGHT-1);
    fruit.shape = '*';

    // we might get either of them at 0, that would place the fruit on the border
    while(fruit.x_position == 0) fruit.x_position = rand()%(WIDTH-1);
    while(fruit.y_position == 0) fruit.y_position = rand()%(HEIGHT-1);

    return fruit;
}

void getFruit(Fruit f){
    printf("fruit shape: %c\n", f.shape);
    printf("fruit x_position: %d\n", f.x_position);
    printf("fruit y_position: %d\n", f.y_position);
}