#include <curses.h>
#include <gameStructs.h>
#include <loadLevel.h>
#include <stdlib.h>


////////////////////////////////////////////////////////FUNCTION HEADERS
void initCurses();
void endCurses();
void debugWait();


///////////////////////////////////////////////////////////MAIN FUNCTION
int main(int argc, char *argv[]){
    path thePath;
    int pathLength;
    tower * towers;
    int nTowers;
    
    towers = loadLevel(&pathLength, &thePath, &nTowers);
    
    /*printf("\nPath coordinates:\n");
    int i;
    for (i = 0; i < pathLength; i++){
        printf("%d,%d\n", thePath.x[i], thePath.y[i]);
    }*/
    
    int i;
    printf("\nTower type and coordinates:\n");
    for (i = 0; i < nTowers; i++){
        printf("%d: %d %d,%d\n", i, towers[i].type, towers[i].x, towers[i].y);
    }
    free (towers);
    
    return 0;
}

////////////////////////////////////////////////////FUNCTION DEFINITIONS
void initCurses(){
    initscr();		//Initialize curses mode
    cbreak();		//Disable input buffering
    noecho();		//Disable echoing
    timeout(0);		//Non-blocking
    curs_set(0);	//Make cursor invisible
}

void endCurses(){
    curs_set(1);	//Turn cursor visible again
    endwin();		//End curses mode
}

/*
* Just a blocking getch() for debuging.
* */
void debugWait(){
    timeout(-1);
    getch();
    timeout(0);
}
