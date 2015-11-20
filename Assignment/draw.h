typedef struct tower{

    int type;
    int x;
    int y;

} tower;

typedef enum towerTypes{
   
    normal,
    missle,
    archer,
    slow
} towerTypes;

void drawTower(tower ** towerArray, int size);
