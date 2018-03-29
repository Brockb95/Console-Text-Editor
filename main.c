#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "edit.h"

int main()
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);
	/* mode variable is declared in "edit.h"
	default mode is insert mode */
	mode = 'i';

	char * fn = "Group 7 is gay";
	printw("Group 7: %s", fn);
	mvwprintw(stdscr, 1, 0, "Insert Mode: "); // default is Insert mode

	getmaxyx(stdscr, y, x);
	WINDOW * win = newwin(50, 80, 3, 0); // create new window
	refresh(); // refresh stdscr

	// create default border around 'win'
	wborder(win, ' ', ' ', '-', ' ', '-', ' ', '-', ' ');
	wrefresh(win);

	// open a file with read and write permission
	char read;
	FILE* file = fopen("file.txt", "r+");
	if (file == NULL){
		wprintw(win, "No file..\n");
		wrefresh(win);
		exit(0);
	}
	wmove(win, 1, 0); // don't overwrite top border
	// display the file in new ncurses window
	read = fgetc(file);
	while(read != EOF){
		wprintw(win, "%c", read);
		read = fgetc(file);
	}
	// choice: user input
	// y and x used to track and move cursor
	int choice, y, x;
	const char filename[] = "file.txt";
	// choice: user input
	// y and x used to track and move cursor
	int choice, y, x;
	while(true){
		wrefresh(win); // refresh screen image
		choice = getch(); // take user input
		getyx(win, y, x); // find cursor position
		//if insert mode
		if(mode == 'i')
		switch(choice){
			case 27:
                commandmodeon();
                break;
			case KEY_LEFT:
                wmoveleft(win);
                break;
			case KEY_RIGHT:
                wmoveright(win);
                break;
			case KEY_UP:
                if (y > 1)
                    wmoveup(win);
                break;
			case KEY_DOWN:
                if (y < 48)
                    wmovedown(win);
                break;
			case KEY_BACKSPACE:
				wbackspace(win);
                break;
            case KEY_DC:
                wdelete(win);
                break;
			case 10: // 10 = new line character
			if(mode == 'i')
				winsertline(win);
                break;
			default: // if no special cases insert character
				winsertchar(win, choice);
                break;
		}
		//if command mode
		else
		switch(choice){
			case KEY_LEFT:
                wmoveleft(win);
                break;
			case KEY_RIGHT:
                wmoveright(win);
                break;
			case KEY_UP:
                if (y > 1)
                    wmoveup(win);
                break;
			case KEY_DOWN:
                if(y < 48)
                    wmovedown(win);
                break;
            case KEY_DC://handles the delete key
                wdelete(win);
			case 'I': // disable command mode
                commandmodeoff(win);
                break;
			case 'X': // delete current line
                wdeleteline(win);
                break;
			case 'O': // insert new line
                winsertline(win);
                break;
            case 'C': //copy text
                copy(win);
                break;
            case 'P': //paste text
                paste(win);
                break;
			default: // invalid
                mvwprintw(stdscr, 62, 0, "Invalid Command.");
                wmove(win, y, x);
                break;
		}
	}
	endwin();

	fclose(file);
	return 0;
}
