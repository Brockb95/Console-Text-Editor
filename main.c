#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "edit.h"
#include "buffer.h"

int main()
{
    initscr();
	cbreak();	
	noecho();
	keypad(stdscr, true);

	// mode variable is declared in "edit.h"
	// default mode is insert mode 
	mode = 'i';


	// open a file with read and write permission
	char read;
	FILE* file = fopen("file.txt", "r+");

	if (file == NULL){
		printw("No file..\n");
		exit(0);
	}
	
	// seeks end of file
	fseek(file, 0, SEEK_END);
	// get size of file
	size = ftell(file);
	rewind(file);
	// allocate space for buffer
	buffer = malloc((size + 1) * sizeof(*buffer));
	// write file to buffer
	fread(buffer, size, 1, file);
	// print buffer to ncurses window
	printw("%s\n", buffer); 

	

	// choice: user input
	// y and x used to track and move cursor
	int choice, y, x, len;
	while(true){
		refresh(); // refresh screen image
		choice = getch(); // take user input
		getyx(stdscr, y, x); // find cursor position
		//if insert mode
		
		if(mode == 'i')
		switch(choice){
			case 27:		// ESC key
			commandmodeon();
			break;
			case KEY_LEFT:
			moveleft();
			break;
			case KEY_RIGHT:
			moveright();
			break;	
			case KEY_UP:
			moveup();
			break;
			case KEY_DOWN:
			movedown();
			break;
			case KEY_BACKSPACE:
			backspace();
			break;
			case 10: // 10 = new line character
			if(mode == 'i'){
				insertline();
			}
			break;
			default: // if no special cases insert character
			//returns 1 if failed, 0 if succeeded
			insertchar(choice); 
			len = strlen(buffer);
     		buffer[len] = choice;
     		buffer[len+1] = '\0';
			break;
		}
		//if command mode
		else
		switch(choice){
			case KEY_LEFT:
			moveleft();
			break;
			case KEY_RIGHT:
			moveright();
			break;	
			case KEY_UP:
			moveup();
			break;
			case KEY_DOWN:
			movedown();
			break;
			case 'I': // disable command mode
			commandmodeoff();
			break;
			case 'X': // delete current line
			deleteline();
			break;
			case 'S':
			file = fopen("file.txt", "w");
			fprintf(file, "%s\n", buffer);
			fclose(file); 
			endwin();
			return 0;	
			break;
			case 'O': // insert new line
			insertline();
			break;
			default: // invalid
			mvprintw(31, 0, "Invalid Command.");
			move(y, x);
			break;
		}
	}
	endwin();
	
	fclose(file); 
	return 0;
}
