#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>
#include "pathInterface.h"
#include "unitInterface.h"

#define TANK_MAX_HP 100
#define NORMAL_MAX_HP 100
#define FAST_MAX_HP 100

typedef enum hi
{
    text = 1,
    red,
    orange,
    green,
    blue
}hi;

typedef enum uTypes
{
  normal,
  fast,
  tank

}uTypes;

void drawMap (path * P,int size);
void drawUnits (path *P, unit ** U,int size);