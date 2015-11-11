#ifndef _DEF_GAMESTRUCTS_H
#define _DEF_GAMESTRUCTS_H

typedef struct st_tower
{
	int type;		//Type of the tower
	int xPos;		//X coordinate
	int yPos;		//Y coordinate
	int damage;		//Damage points
	int fireRate;	//Attack rate of the tower
	int frCounter;	//Attack rate counter
	int range;		//Maximum range distance of attack
} tower;

typedef struct st_path
{
	int length;
	int *xPos;	//Array of X coordinates of each path position
	int *yPos;	//Array of Y coordinates of each path position
} path;

#endif
