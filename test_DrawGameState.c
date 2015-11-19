#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>
#include "pathInterface.h"
#include "testEnvironment.h"
#include "DrawGameState.h"

typedef enum uTypes
{
  normal,
  fast,
  tank

}uTypes;
typedef enum hi
{
    text = 1,
    red,
    orange,
    green,
    blue
}hi;

int main (void)
{

    
    char uInput= ' ';
    path *P;
    unit ** U;
    int i;

    U = malloc(sizeof(unit*) * 10);
    P = createPath(20, 3);

    for (i = 0; i < 10; i++)
    {
        U[i] = createUnit(0,P->x[i],P->y[i]);
        U[i]->health = U[i]->health - (i * 10);
        U[i]->pathIndex = i;

        U[i]->type = i%3;
        printf("%d\n",U[i]->x);
    }
    getch();
    initscr();
    start_color();

    init_pair(text, 7,0);
    init_pair(blue, 4,0);
    init_pair(red, 1,0);
    init_pair(orange, 3,0);
    init_pair(green, 2,0);

    while (uInput != 'q')
    {
        drawMap(P,20);
        drawUnits(P,U,10);
        refresh();
    	uInput = getch();
    }
    endwin();
    printPath(P,20);

	return(0);
}