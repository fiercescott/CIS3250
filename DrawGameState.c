#include "DrawGameState.h"

/*TODO
*
* Figure out max health of each unit. Currently The max hp of
* each unit type is defined in DrawGameState.h. 
* I calculate each units percent hp (current hp / max hp) to determine 
* what colour to draw them in draw units.
*
* In draw Map: figure out if path is in slow range.
* Perhaps we can store a 'int slowed[PATH_SIZE]' vairable in struct path 
* where each path index could be set to '1' if that path index
* is in range of a slow tower.
*/







void drawMap (path * P,int size)
{
  	int i;
    for (i = 0; i < size; i++)
    {
        /*CHANGE THIS!!!!!!!*/
   	    if ( i > size - 10) /*CHANGE TO IF IN RANGE OF SlOW */
        {
    	    attron(COLOR_PAIR(blue));
        }
        mvprintw(P->x[i],P->y[i], "X");
        attron(COLOR_PAIR(text));
    }
}

/*NEED TO FIGURE OUT HOW TO DRAW FASTEST UNIT ON TOP*/
void drawUnits (path * P, unit ** U,int size)
{
    int i;
    char unitSymbol;
    double percent = 0;
    for (i = 0; i < size; i++)
    {
        /*Determine type and figure out what to print*/
        /*Calculate percent of health remaining bassed off of Max HP of that unit type*/
        /*THOUGHT: include an 'int maxHealth' variable in the unit struct and set it to the 
          Initial health of that unit*/

        /*CHANGE DEFINED MAX_HP STUFF*/
        if (U[i]->type == normal)
        {
            unitSymbol = 'n';
            percent = (double)U[i]->health / (double)NORMAL_MAX_HP;
        }
        else if (U[i]->type == fast)
        {
            unitSymbol = 'f';
            percent = (double)U[i]->health / (double)FAST_MAX_HP;
        }
        else if (U[i]->type == tank)
        {
            unitSymbol = 't';
            percent = (double)U[i]->health / (double)TANK_MAX_HP;
        }

        /*If unit is not dead, Draw it*/
        if (percent != 0)
        {
            /*Set Colour to draw based on percent*/
            /*LOW HP*/
            if (percent <= .33)
            {
                attron(COLOR_PAIR(red));
            }
            /*MEDIUM HP*/
            else if (percent > .33 && percent <=.66)
            {
                attron(COLOR_PAIR(orange));
            }
            /*GOOD HP*/
            else
            {
                attron(COLOR_PAIR(green));
            }
            /*Draw the unit on the screen based off of path index*/
            mvprintw(P->x[U[i]->pathIndex],P->y[U[i]->pathIndex], "%c", unitSymbol);
            attron(COLOR_PAIR(text));
        }
    }   
}
