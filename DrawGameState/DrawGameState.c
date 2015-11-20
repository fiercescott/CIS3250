#include "DrawGameState.h"

/*TODO
*
*
* In draw Map: figure out if path is in slow range.
* Perhaps we can store a 'int slowed[PATH_SIZE]' vairable in struct path 
* where each path index could be set to '1' if that path index
* is in range of a slow tower.
*/


/*NEED THIS SOMEWHERE FOR COLOUR*/
typedef enum colours
{
    /*MAYBE NOT TEXT, need to research atroff*/
    text = 1,
    red,
    orange,
    green,
    blue
}colours;


/*MAY NOT USE ENUMS FOR ACTUAL IMPLEMENTAION*/
typedef enum uTypes
{
  normal,
  fast,
  tank

}uTypes;

typedef enum towerTypes{
   
    NORMAl,
    missle,
    archer,
    slow
} towerTypes;




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
        mvprintw(P->y[i],P->x[i], "X");
        attron(COLOR_PAIR(text));
    }
}

void drawUnits (path * P, unit ** U,int uSize, int pSize)
{
    int i;
    char unitSymbol;
    double percent = 0;
    int *unitOnPath;
    int drawX, drawY, validDraw;

    unitOnPath = malloc(sizeof(int)*pSize);
    for (i = 0; i < pSize; i++)
    {
        unitOnPath[i] = -1;
    }
    
    for (i = 0; i < uSize; i++)
    {
        validDraw = 1;

        /*the location to draw each unit*/
        drawX = P->x[U[i]->pathIndex] ;
        drawY = P->y[U[i]->pathIndex];

        /*Determine type and figure out what to print*/
        /*Calculate percent of health remaining bassed off of Max HP of that unit type*/
        if (U[i]->type == tank)
        {
            unitSymbol = 't';
            percent = (double)U[i]->health / (double) U[i]->maxHealth;
            /*Dont draw if normal is fast unit is occupying the pathIndex*/
            if (unitOnPath[U[i]->pathIndex] == normal || unitOnPath[U[i]->pathIndex] == fast)
            {
                validDraw = 0;
            }
            /* else: add unit to path*/
            else
            {
                unitOnPath[U[i]->pathIndex] = tank;   
            }
        }
        else if (U[i]->type == normal)
        {
            unitSymbol = 'n';
            percent = (double)U[i]->health / (double)U[i]->maxHealth;
            /*Dont draw if fast unit is occupying the pathIndex*/
            if (unitOnPath[U[i]->pathIndex] == fast)
            {
                validDraw = 0;
            }
            /* else: add unit to path*/
            else
            {
                unitOnPath[U[i]->pathIndex] = normal;
            }
        }
        else if (U[i]->type == fast)
        {
            unitSymbol = 'f';
            percent = (double)U[i]->health / (double)U[i]->maxHealth;
            /*Always draw, add unit onto pathIndex*/
            unitOnPath[U[i]->pathIndex] = fast;   
        }

        /*If unit is not dead, and drawing is allowed Draw it*/
        if (percent != 0 && validDraw)
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

            mvprintw(drawY,drawX, "%c", unitSymbol);
            attron(COLOR_PAIR(text));
        }
    } 
    free(unitOnPath);  
}

void drawTowers(tower ** towerArray, int size)
{

    int i = 0;
    int tempX = 0;
    int tempY = 0;
    

    for(i = 0;i < size; i++) 
    {

        tempX = towerArray[i]->x;
        tempY = towerArray[i]->y;
        
        /*Draw towers based on type*/
        if (towerArray[i]->type == NORMAl)
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
