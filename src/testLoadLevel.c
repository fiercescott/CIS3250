#include <curses.h>
#include <gameStructs.h>
#include <loadLevel.h>


////////////////////////////////////////////////////////FUNCTION HEADERS
void initCurses();
void endCurses();
void debugWait();


///////////////////////////////////////////////////////////MAIN FUNCTION
int main(int argc, char *argv[])
{
	initCurses();
	
	if (argc <= 1)
	{
		printw("Gimme some files.");
		refresh();
		debugWait();
		
		endCurses();
		
		return 0;
	}
	
	//Discard the first argument (it is the name of the program) and decrement counter
	argv++;
	argc--;
	
	//Load the levels from the files passed as arguments to the program
	if (loadLevel(argc, argv))
		printw("\nSuccessfully loaded all the files.");
	else
		printw("\nThere was a problem reading one of the files.");
	refresh();
	debugWait();
	
	endCurses();
	
	return 0;
}


////////////////////////////////////////////////////FUNCTION DEFINITIONS
void initCurses()
{
	initscr();		//Initialize curses mode
	cbreak();		//Disable input buffering
	noecho();		//Disable echoing
	timeout(0);		//Non-blocking
	curs_set(0);	//Make cursor invisible
}

void endCurses()
{
	curs_set(1);	//Turn cursor visible again
	endwin();		//End curses mode
}

/*
 * Just a blocking getch() for debuging.
 * */
void debugWait()
{
	timeout(-1);
	getch();
	timeout(0);
}

