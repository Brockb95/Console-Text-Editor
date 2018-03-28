#include <ncurses.h>
#include <stdlib.h>

int y, x;
char mode; // stores the current mode of the editor
char * buffer, filename;
/* move*() functions move the cursor one space*/
void moveup(); // move up in stdscr
void wmoveup(WINDOW * win); // move up in window 'win'

void movedown(); // move down in stdscr
void wmovedown(WINDOW * win); // move down in window 'win'

void moveleft(); // move left in stdscr
void wmoveleft(WINDOW * win); // move left in window 'win'

void moveright(); // move right in stdscr
void wmoveright(WINDOW * win); // move right in window 'win

void deleteline(); // delete current line
void wdeleteline(WINDOW * win); // delete current line in window 'win'

void backspace(); // delete the character to the left of the cursor
void wbackspace(WINDOW * win); // delete the char to the left in 'win'

void insertline(); // insert a line at current position
void winsertline(WINDOW * win); // insert a line into window 'win'

void insertchar(char c); // inserts a character 'c' at current position
void winsertchar(WINDOW * win, char c); // inserts a character 'c' into window 'win'

void printbuffer(); 

void savefile();

void commandmodeon(WINDOW * win); // enable command mode
void commandmodeoff(WINDOW * win); // disable command mode

void write_to_file(const char *);
int fsize(const char *);
void searchReplace(const char *, const char *, const char *);
