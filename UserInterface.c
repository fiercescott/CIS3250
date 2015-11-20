//Made by Scott Collier
//CIS 3250
//Reverse Tower Defence: User Interface

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

//unit struct as described in document
typedef struct unit
{
    char type;
    int health;
    int maxHealth;
    int speed;
    int xPos;
    int yPos;
    int positionIndex;
}unit;

//declaration of functions
void createInterface(int xPos, int yPos);
void manageUserInput(int xPos, int yPos);
void createUnits(unit ** unitArray, char selectionChar, int * costPointer, int * sizePointer);
void runGame(unit ** unitArray);


//main function
int main()
{
    initscr();
    cbreak();
    noecho();
    
    //set reference x and y position so it can be placed at desired position
    int xPos;
    int yPos;
    
    xPos = 15;
    yPos = 7;
    
    createInterface(xPos, yPos);
    manageUserInput(xPos, yPos);
    
    endwin();
    
    return 0;
}


//Function: createInterface
//Takes in a x and y value for positioning reference
//This function draws to the screen the menu and interface of the user
void createInterface(int xPos, int yPos)
{
    int i;
    
    i = 0;
    
    //Create menu box
    for(i = 0; i < 20; i++)
    {
        mvaddch(i + yPos,0 + xPos,'X');
    }
    
    for(i = 0; i < 21; i++)
    {
        mvaddch(i + yPos,30 + xPos,'X');
    }
    
    for(i = 0; i < 30; i++)
    {
        mvaddch(0 + yPos,i + xPos,'X');
    }
    
    for(i = 0; i < 30; i++)
    {
        mvaddch(20 + yPos,i + xPos,'X');
    }
    
    //Prints menu contents
    mvprintw(2 + yPos, 3 + xPos, "Points:");
    mvprintw(3 + yPos, 3 + xPos, "Unit Select:");
    mvprintw(4 + yPos, 3 + xPos, "Normal Unit:  n");
    mvprintw(5 + yPos, 3 + xPos, "HP 30 Speed 2 Cost 100");
    mvprintw(6 + yPos, 3 + xPos, "Speed Unit:   f");
    mvprintw(7 + yPos, 3 + xPos, "HP 15 Speed 3 Cost 100");
    mvprintw(8 + yPos, 3 + xPos, "Tank Unit:    t");
    mvprintw(9 + yPos, 3 + xPos, "HP 60 Speed 1 Cost 100");
    mvprintw(10 + yPos, 3 + xPos, "Remove Last Unit:");
    mvprintw(12 + yPos, 3 + xPos, "Run Game");
    mvprintw(14 + yPos, 3 + xPos, "Quit Game");
    mvprintw(16 + yPos, 3 + xPos, "Current Units:");
    
    refresh();
    
}





//Function: manageUserInput
//Takes in x and y value for positioning reference
//Move up with the "w" key, down with the "s" key, and select with the "z" key
void manageUserInput(int xPos, int yPos)
{
    //initialize variables
    int i;
    int j;
    char input;
    unit ** unitArray;
    int arraySize;
    char selectionChar;
    int cost;
    int *costPointer;
    int displayXPos;
    int *sizePointer;
    int curserX;
    int curserY;
    
    
    
    i = 0;
    j = 0;
    curserX = 2 + xPos;
    curserY = 4 + yPos;
    input = ' ';
    arraySize = 0;
    selectionChar = ' ';
    cost = 1000;
    displayXPos = 0 + xPos;
    
    //designate pointers
    costPointer = &cost;
    sizePointer = &arraySize;
    
    //malloc memory for unit array
    unitArray = malloc(sizeof(unit)*30);
    
    mvaddch(curserY, curserX, '>');

    
    //read player input and act upon it
    while (i == 0)
    {
        //print amount of points the user has to purchase units
        mvprintw(2 + yPos, 12 + xPos, "     ");
        mvprintw(2 + yPos, 12 + xPos, "%d", cost);
        move(curserY,curserX);
        
        input = getch();
        
        switch (input)
        {
                //move up if 'w' is pressed
            case 'w':
                if(curserY - 2 >= 4 + yPos )
                {
                    mvaddch(curserY, curserX,' ');
                    curserY = curserY - 2;
                    mvaddch(curserY, curserX, '>');
                }
                break;
                
                //move down if 's' is pressed
            case 's':
                if(curserY + 2 <= 14 + yPos)
                {
                    mvaddch(curserY,curserX,' ');
                    curserY = curserY + 2;
                    mvaddch(curserY, curserX, '>');
                }
                break;
                
                
            //Do an action when the action key "z" is selected
            case 'z':
                //add an unit to the array
                if ((curserX == 2 + xPos)&&(curserY == 4 + yPos))
                {
                    selectionChar = 'n';
                    createUnits(unitArray,selectionChar,&cost, &arraySize);
                }
                if ((curserX == 2 + xPos)&&(curserY == 6 + yPos))
                {
                    selectionChar = 'f';
                    createUnits(unitArray,selectionChar,&cost, &arraySize);
                }
                if ((curserX == 2 + xPos)&&(curserY == 8 + yPos))
                {
                    selectionChar = 't';
                    createUnits(unitArray,selectionChar,&cost, &arraySize);
                }
                
                //removes an element of the array
                if  ((curserX == 2 + xPos)&&(curserY == 10 + yPos))
                {
                    if(arraySize > 0)
                    {
                        if(unitArray[arraySize - 1]->type == 'n')
                        {
                            cost = cost + 100;
                        }
                        if(unitArray[arraySize - 1]->type == 'f')
                        {
                            cost = cost + 100;
                        }
                        if(unitArray[arraySize - 1]->type == 't')
                        {
                            cost = cost + 100;
                        }
                        free(unitArray[arraySize-1]);
                        arraySize = arraySize - 1;
                    }

                    break;
                }
                
                // run game
                if ((curserX == 2 + xPos)&&(curserY == 12 + yPos))
                {
                    unitArray = realloc(unitArray, sizeof(unit)*arraySize);
                    //runGame(unitArray);
                    break;
                }
                
                // quit game
                if ((curserX == 2 + xPos)&&(curserY == 14 + yPos))
                {
                    clear();
                    refresh();
                    i = 1;
                    break;
                }
                break;
        }
        
        
        
        //display units selectied beside "Units Selected:"

        
        if (arraySize >= 5)
        {
            mvprintw(18 + yPos, 2 + xPos, "           ");
            mvprintw(19 + yPos, 2 + xPos, "           ");
            displayXPos = 3 + xPos;
            for(j=0; j<5; j++)
            {
                mvaddch(18 + yPos, displayXPos, unitArray[j]->type);
                displayXPos = displayXPos + 2;
            }
            
            displayXPos = 3 + xPos;
            
            for(j=5; j<arraySize; j++)
            {
                mvaddch(19 + yPos, displayXPos, unitArray[j]->type);
                displayXPos = displayXPos + 2;
            }
        }
        
        else if (arraySize < 5)
        {
            mvprintw(18 + yPos, 3 + xPos, "          ");
            mvprintw(19 + yPos, 3 + xPos, "          ");
            displayXPos = 3 + xPos;
            for(j=0; j<arraySize; j++)
            {
                mvaddch(18 + yPos, displayXPos, unitArray[j]->type);
                displayXPos = displayXPos + 2;
            }
        }
        
        move (curserY + yPos,curserX + xPos);
        refresh();
    }
}



//just takes in a value,creates the unit, adds it to the array, and subtracts from points
//dont know if I gotta do anything for xPos or yPos so I just left at zero
//any value is subject to change, decide on the cost of units

//Function: createUnits
//Is passed the unit array, the selected unit, the amount of points the user has, and the array size
void createUnits(unit ** unitArray, char selectionChar, int * costPointer, int * sizePointer)
{
    
    unit * unitVar;
    
    int isAllowed;
    
    isAllowed = 0;
    
    switch(selectionChar)
    {
            //create normal unit
        case 'n':
            
            //If the user has enough points, create the unit
            if (*costPointer - 100 >= 0)
            {
                *costPointer = *costPointer - 100;
                isAllowed = 1;
                unitVar = malloc(sizeof(unit));
            
                unitVar->type = 'n';
                unitVar->health = 30;
                unitVar->maxHealth = 30;
                unitVar->speed = 2;
                unitVar->xPos = 0;
                unitVar->yPos = 0;
                unitVar->positionIndex = 0;
            }
            
            break;
            
            //create fast unit
        case 'f':
            if (*costPointer - 100 >= 0)
            {
                *costPointer = *costPointer - 100;
                isAllowed = 1;
                unitVar = malloc(sizeof(unit));
                
                unitVar->type = 'f';
                unitVar->health = 15;
                unitVar->maxHealth = 15;
                unitVar->speed = 3;
                unitVar->xPos = 0;
                unitVar->yPos = 0;
                unitVar->positionIndex = 0;
            }
            
            break;
            
            //create tank unit
        case 't':
            if (*costPointer - 100 >= 0)
            {
                *costPointer = *costPointer - 100;
                isAllowed = 1;
                unitVar = malloc(sizeof(unit));
                
                unitVar->type = 't';
                unitVar->health = 60;
                unitVar->maxHealth = 60;
                unitVar->speed = 1;
                unitVar->xPos = 0;
                unitVar->yPos = 0;
                unitVar->positionIndex = 0;
            }
            
            break;
    }
    
    //add unit to array
    if(isAllowed == 1)
    {
        unitArray[*sizePointer] = unitVar;
        *sizePointer = *sizePointer + 1;

    }
    
    
}



void runGame(unit ** unitArray)
{
    
    //send the unit array to some other function to start game
}
