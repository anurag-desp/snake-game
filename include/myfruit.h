#pragma once

typedef struct fruit{
    int x_position;
    int y_position;
    char shape;
} Fruit;


Fruit setFruit();   // To put a fruit at a random coordinate inside the border
void getFruit();    // To get the coordinates of the current fruit