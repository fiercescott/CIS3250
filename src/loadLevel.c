#include <curses.h>
#include <gameStructs.h>
#include <string.h>
#include <stdlib.h>


////////////////////////////////////////////////////FUNCTION DEFINITIONS
/* 
 * Reads the files passed as arguments, parses the level information in 
 * the files, builds the paths and initializes the towers from each level.
 * 
 * int nFiles: Number of files to read.
 * char *levelFiles[]: Array with the paths for each level file.
 * 
 * Returns 0 if some error occured when parsing any of the files. Returns
 * 1 if loading was successful.
 * */
int loadLevel(int nFiles, char *levelFiles[])
{
	int i;
	for (i = 0; i < nFiles; i++)
	{
		printw("\n%s", levelFiles[i]);
		if (!readLevelFile(levelFiles[i]))
			return 0;  //Some problem occured with this file. Return with error
	}
	
	return 1;
}

/*
 * Opens the file passed as argument and parses the level information.
 * 
 * char levelFile[]: Path to the level file.
 * 
 * Returns 0 if the file could not be opened or if the file does not follow
 * the correct pattern. Returns 1 on success.
 * */
int readLevelFile(char levelFile[])
{
	//Open file for reading
	FILE *file;
	file = fopen(levelFile, "r");
	if (file == NULL)  //Could not open file
		return 0;
	
	/*printw("\nFile opened");
	refresh();*/
	
	int width, height;		//Map dimensions
	int startX, startY;		//Coordinates of first position of the path
	int endX, endY;			//Coordinates of last position of the path
	int nTowers;			//Number of towers in the level
	
	//Read level info
	if (fscanf(file, "%d", &width) == EOF)		return 0;
	if (fscanf(file, "%d", &height) == EOF)		return 0;
	if (fscanf(file, "%d", &startX) == EOF)		return 0;
	if (fscanf(file, "%d", &startY) == EOF)		return 0;
	if (fscanf(file, "%d", &endX) == EOF)		return 0;
	if (fscanf(file, "%d", &endY) == EOF)		return 0;
	if (fscanf(file, "%d", &nTowers) == EOF)	return 0;
	
	printw("\nNum of towers: %d", nTowers);
	refresh();
	
	//Read map
	char rawMap[height][width];
	char temp[width+1];  //+1 space for the terminating null character
	int i;
	for (i = 0; i < height; i++)
	{
		//Read line from file and store in temp
		if (fscanf(file, "%s", &temp) == EOF) return 0;
		
		//Copy line read to the 2 dimensional array
		strncpy(rawMap[i], temp, width);
		
		printw("\n");
		int j;
		for (j = 0; j < width; j++)
			printw("%c", rawMap[i][j]);
		refresh();
	}
	
	fclose(file);
	
	//buildMap();
	
	//initializeTowers();
	
	return 1;  //Return with success
}
