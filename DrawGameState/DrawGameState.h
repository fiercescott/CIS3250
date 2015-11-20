#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>

/*.h files for the path, unit and towers. CURRENTLY THE TEST ENVIRONMENT ONES*/
#include "pathInterface.h"
#include "unitInterface.h"
#include "towerInterface.h"


/*  drawMap
 *
 *  Requires: A pointer to the path the units are following and its size (int)
 *  Purpose:  To draw the path the units will be following. 
 */
void drawMap (path * P,int size);
 
 /*  drawUnits
 *
 *  Requires: A pointer to the path the units are following (path *), its size (int),
 *            A pointer to the array of units in play (unit **) and its size (int)
 *  Purpose:  To draw the units onto the screen 
 */
void drawUnits (path *P, unit ** U, int uSize, int pSize);

/*  drawTowers
 *
 *  Requires: A pointer to the array of towers (tower **) and its size (int)
 *  Purpose:  To draw the towers onto the map. 
 */
void drawTowers (tower ** towerArray, int size);