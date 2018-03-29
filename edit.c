#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "edit.h"

// move the cursor up one position
void moveup()
{	
	getyx(stdscr, y, x);
	move(y - 1, x);
}
// move the cursor up one position in window 'win'
void wmoveup(WINDOW * win){
	getyx(win, y, x);
	wmove(win, y - 1, x);
}
// move the cursor down one position
void movedown(){
	getyx(stdscr, y, x);
	move(y + 1, x);
}
// move the cursor down one position in window 'win'
void wmovedown(WINDOW * win){
	getyx(win, y, x);
	wmove(win, y + 1, x);
}
// move the cursor left one postion
void moveleft(){
	getyx(stdscr, y, x);
	move(y, x - 1);
}
// move the cursor left one position in window 'win'
void wmoveleft(WINDOW * win){
	getyx(win, y, x);
	wmove(win, y, x - 1);
}
// move the cursor right one position
void moveright(){
	getyx(stdscr, y, x);
	move(y, x + 1);
}
// move the cursor right one position in window 'win'
void wmoveright(WINDOW * win){
	getyx(win, y, x);
	wmove(win, y, x + 1);
}
// delete the current line
void deleteline(){
	deleteln();
}
// delete line in window 'win'
void wdeleteline(WINDOW * win){
	wdeleteln(win);
}
// insert a line at the current position
void insertline(){
	getyx(stdscr, y, x);
	insertln();
	move(y + 1, x);
}
// insert a line into window 'win'
void winsertline(WINDOW * win){
	getyx(win, y, x);
	winsertln(win);
	wmove(win, y + 1, x);
}
// delete the character to the left of the cursor
void backspace(){
	getyx(stdscr, y, x);
	mvdelch(y, x - 1);
}
// delete the character to the left in window 'win'
void wbackspace(WINDOW * win){
	getyx(win, y, x);
	mvwdelch(win, y, x - 1);
}
// irt a character and shift line to the right
void insertchar(char c){
	getyx(stdscr, y, x);
	insch(c);
	move(y, x + 1);	
}
// insert a character to a specified window
void winsertchar(WINDOW* win, char c){
	getyx(win, y, x);
	winsch(win, c);
	wmove(win, y, x + 1);
}
// enable command mode
void commandmodeon(WINDOW * win){
	getyx(win, y, x);
	mvwprintw(stdscr, 1, 0, "Command Mode: ");
	//mvwprintw(stdscr, 2, 0, 
	//"\'I\': Enter Insert Mode \'X\': Delete Line \'O\': Insert Line \'S\': Save File \'C\': Copy \'P\': Paste \'R\':
	//Search");
	wmove(win, y, x);
	mode = 'c';
}
// disable command mode
void commandmodeoff(WINDOW * win){
	getyx(stdscr, y, x);
	mvwprintw(stdscr, 1, 0, "Insert Mode: ");
	wmove(win, y, x);
	mode = 'i';
}
//to search and replace
void searchReplace(char* str, const char* old, const char* new){
    char choice;
    while (choice == 'R' || choice == 'r'){

    	int old_len, new_len;
    	char *s, *d;
    	char * tmpbuf;

    	if (!str || !*str || !old || !*old || !new)
		return;
    	tmpbuf = malloc(strlen(str) + 1);
    	if (tmpbuf == NULL)
		return;

    	old_len = strlen(old);
    	new_len = strlen(new);

    	s = str;
    	d = tmpbuf;
 
    	while(*s){
		if(strncmp(s, old, old_len) == 0){
        		strcpy(d, new);
   			s += old_len;
			d += new_len;
        	}
		else
			*d++ = *s++;
   	}
		*d = '\0';
		strcpy(str, tmpbuf);
		free(tmpbuf);
       
     }  
}
void writer(char* str){
	FILE* in;
	if((in = fopen("file2.txt", "w")) == NULL){
		printf("error...");
		exit(1);
	}
	int c;
	while((c = getchar()) != EOF)
		fputc(c, in);
	printf(str, in);
	fclose(in);
}
