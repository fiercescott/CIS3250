#include <curses.h>
#include <gameStructs.h>
#include <string.h>
#include <stdlib.h>


////////////////////////////////////////////////////FUNCTION DEFINITIONS
int isInBounds(int y, int x, int height, int width){
    if (y < 0 || y >= height)
        return 0;
    if (x < 0 || x >= width)
        return 0;
    
    return 1;
}

tower * loadLevel (char * filename, int * pathLength, path * thePath, int * nTowers){
    FILE * file = fopen(filename, "r");
    if (file == NULL) return NULL;
    
    int height = 0;
    int width = 0;
    int num = 0;
    int count = 0;
    int numT = 0;
    int tCount;
    tower * towers = NULL;
    
    if (fscanf(file, "%d %d", &width, &height) == EOF) return NULL;
    if (fscanf(file, "%d", nTowers) == EOF) return NULL;
    
    char levelString [height][width+1];
    char temp[width + 1];
    tCount = *nTowers;
    towers = (tower*)malloc (sizeof (tower) * tCount);
    
    int i;
    for (i = 0; i < height; i++){
        if (fscanf(file, "%s", temp) == EOF) return NULL;
        strncpy(levelString[i], temp, width);
    }
    
    //Initialize towers
    int startX, startY;
    int x, y;
    for (x = 0; x < width; x++){
        for (y = 0; y < height; y++){
            if (levelString[y][x] == '+'){
                num++;
            }
            else if (levelString[y][x] == '='){
                startX = x;
                startY = y;
                num++;
            }
            else if (levelString[y][x] == '$'){
                num++;
            }
            else if (levelString[y][x] == 'N'){
                towers[numT].type = NORMAL;
                towers[numT].x = x;
                towers[numT].y = y;
                towers[numT].fireRate = 5;
                towers[numT].counter = 1;
                towers[numT].damage = 5;
                towers[numT].range = 5;
                numT++;
            }
            else if (levelString[y][x] == 'M'){
                towers[numT].type = MISSILE;
                towers[numT].x = x;
                towers[numT].y = y;
                towers[numT].fireRate = 3;
                towers[numT].counter = 1;
                towers[numT].damage = 10;
                towers[numT].range = 8;
                numT++;
            }
            else if (levelString[y][x] == 'A'){
                towers[numT].type = ARCHER;
                towers[numT].x = x;
                towers[numT].y = y;
                towers[numT].fireRate = 7;
                towers[numT].counter = 1;
                towers[numT].damage = 3;
                towers[numT].range = 10;
                numT++;
            }
            else if (levelString[y][x] == 'S'){
                towers[numT].type = SLOW;
                towers[numT].x = x;
                towers[numT].y = y;
                towers[numT].fireRate = 5;
                towers[numT].counter = 1;
                towers[numT].damage = 0;
                towers[numT].range = 7;
                numT++;
            }
        }
    }
    
    *pathLength = num;
    
    //Build path
    int index = 0;  //Index of the path position
    y = startY;
    x = startX;
    int nextY, nextX;  //Next neighbour position being checked
    int deltaY, deltaX;  //Current position - previous position (direction from previous to current)
    
    //Initialize search direction
    if (startX == 0){
        //Path starts at left side and goes to the right
        deltaY = 0;
        deltaX = 1;
    }
    else if (startX == width-1){
        //Path starts at right side and goes to the left
        deltaY = 0;
        deltaX = -1;
    }
    else if (startY == 0){
        //Path starts at top side and goes to the bottom
        deltaY = 1;
        deltaX = 0;
    }
    else{
        //Path starts at bottom side and goes to the top
        deltaY = -1;
        deltaX = 0;
    }
    
    //Store starting position of the path
    thePath->x[index] = x;
    thePath->y[index] = y;
    index++;

    while (index < *pathLength){
        //Check position directly opposite from previous path position
        if (isInBounds((nextY = y+deltaY), (nextX = x+deltaX), height, width)){
            if (levelString[nextY][nextX] == '+' || levelString[nextY][nextX] == '$'){
                //Found next position
                y = nextY;
                x = nextX;
                thePath->x[index] = x;
                thePath->y[index] = y;
                index++;
                continue;  //Continue search
            }
        }
        
        //Check positions in each side of current position
        if (isInBounds((nextY = y+deltaX), (nextX = x+deltaY), height, width)){
            if (levelString[nextY][nextX] == '+' || levelString[nextY][nextX] == '$'){
                //Found next position
                deltaY = nextY - y;
                deltaX = nextX - x;
                y = nextY;
                x = nextX;
                thePath->x[index] = x;
                thePath->y[index] = y;
                index++;
                continue;  //Continue search
            }
        }
        if (isInBounds((nextY = y-deltaX), (nextX = x-deltaY), height, width)){
            if (levelString[nextY][nextX] == '+' || levelString[nextY][nextX] == '$'){
                //Found next position
                deltaY = nextY - y;
                deltaX = nextX - x;
                y = nextY;
                x = nextX;
                thePath->x[index] = x;
                thePath->y[index] = y;
                index++;
                continue;  //Continue search
            }
        }
        
        //If it didn't enter any of the ifs above, the path in the level file has some error
        free(towers);
        return NULL;
    }
    
    return towers;
}
