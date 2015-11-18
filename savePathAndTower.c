#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARRAY_SIZE 1000
#define NORMAL 0
#define MISSILE 1
#define ARCHER 2
#define SLOW 3

typedef struct path{
    int x[ARRAY_SIZE];
    int y[ARRAY_SIZE];
} path;

typedef struct tower{
    int type;
    int x;
    int y;
    int fireRate;
    int counter;
    int damage;
    int range;
} tower;

tower * savePathAndTowers (char * filename, int * pathLength, path * thePath, int * nTowers);

int main(int argc, char * argv[]){
  int pLength = 0;
  int nTowers = 0;
  path thePath;

  tower * towers = savePathAndTowers(argv[1], &pLength, &thePath, &nTowers);

  printf("\nPath coordinates:\n");
  for (int i = 0; i < pLength; i++){
    printf("%d,%d\n", thePath.x[i], thePath.y[i]);
  }

  printf("\nTower type and coordinates:\n");
  for (int i = 0; i < nTowers; i++){
    printf("%d: %d %d,%d\n", i, towers[i].type, towers[i].x, towers[i].y);
  }
  free (towers);

  return 0;
}

tower * savePathAndTowers (char * filename, int * pathLength, path * thePath, int * nTowers){
  FILE * file = fopen(filename, "r");
  if (file == NULL) return NULL;

  int height = 0;
  int width = 0;
  int num = 0;
  int count = 0;
  int numT = 0;
  int tCount;
  tower * towers = NULL;

  if (fscanf(file, "%d %d", &width, &height) == EOF)		return NULL;
  if (fscanf(file, "%d", nTowers) == EOF) return NULL;

  char levelString [height][width+1];
  char temp[width + 1];
  tCount = *nTowers;
  towers = (tower*)malloc (sizeof (tower) * tCount);

  for (int i = 0; i < height; i++)
	{
		if (fscanf(file, "%s", temp) == EOF) return NULL;
		strncpy(levelString[i], temp, width);
  }

  for (int x = 0; x < width; x++){
    for (int y = 0; y < height; y++){
      if (levelString[y][x] == '+'){
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

  for (int x = 0; x < width; x++){
    for (int y = 0; y < height; y++){
      if (levelString[y][x] == '+'){
        thePath->x[count] = x;
        thePath->y[count] = y;
        count++;
      }
    }
  }

  return towers;
}
