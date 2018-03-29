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
// insert a character and shift line to the right
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
//gets an array of char from user that they want copied
void copy(WINDOW * win){
    wprintw(win, "Enter text to copy (end with ';'): ");//prompt for copy text
    int i;
	int k;//used for loops
    for(i = 0; i <= SIZE - 1; i++){
        int input = getch();//get char from user
        if (i == SIZE - 1)
            input = ';';//forced quit
        switch(input){//deal with special keys
            case KEY_LEFT:
                i--;//don't count this iteration
                break;
			case KEY_RIGHT:
                i--;
                break;
			case KEY_UP:
                i--;
                break;
			case KEY_DOWN:
                i--;
                break;
			case KEY_BACKSPACE:
				if(i > 0){//make sure there is something to backspace
				wbackspace(win);
				i = i - 2;
				}
				break;
            case KEY_DC:
                i--;
                break;
            case 59://ascii for ;
                pasted[i] = input;
                k = i;
                i = SIZE;
                break;
            default:
                pasted[i] = input;
                winsertchar(win, input);//puts char on screen
                break;
            }
        }
        for(int j = 0; j < k + 35; j++){//deletes what you entered and the printw line
            wbackspace(win);
        }//gets rid of text
    }
void paste(WINDOW * win){
    for(int i = 0; i < SIZE - 1; i++){
        if(pasted[i] == ';')//check for end line char
            break;//stops at semicolon if you don't use entire array
        else
            winsertchar(win, pasted[i]);
    }//uses insertchar because that's technically happening anyway
}
