#include "draw.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

void drawTower(tower ** towerArray, int size)
{


    int i = 0;
    int tempX = 0;
    int tempY = 0;

    

    for(i = 0;i < size; i++) 
    {

        tempX = towerArray[i]->x;
	tempY = towerArray[i]->y;

        if (towerArray[i]->type == normal)
	{
            mvprintw(tempY,tempX,"N");    
	}
	else if (towerArray[i]->type == missle)
	{
	    mvprintw(tempY,tempX,"M");
	}
	else if (towerArray[i]->type == archer)
	{
	    mvprintw(tempY,tempX,"A");
	}
        else if (towerArray[i]->type == slow)
	{
	    mvprintw(tempY,tempX,"S");
	}
    }

}
