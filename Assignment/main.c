#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "draw.h"

int main()
{

    int size = 3;

    tower ** towerArray = malloc(sizeof(tower)*3);

    towerArray[0]=malloc(sizeof(tower));
    towerArray[0]->x = 2;
    towerArray[0]->y = 1;
    towerArray[1]=malloc(sizeof(tower));
    towerArray[1]->x = 3;
    towerArray[1]->y = 3;
    towerArray[2]=malloc(sizeof(tower));
    towerArray[2]->x = 5;
    towerArray[2]->y = 7;

    towerArray[0]->type = 0;
    towerArray[1]->type = 1;
    towerArray[2]->type = 2;
    
    initscr();
    drawTower(towerArray, size);
    refresh();
    getchar();
    endwin();
    free(towerArray);
}
