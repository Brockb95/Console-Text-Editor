#include "edit.h"

// move the cursor up one position
void moveup()
{
	getyx(stdscr, y, x);
	move(y - 1, x);
}
// move the cursor down one position
void movedown(){
	getyx(stdscr, y, x);
	move(y + 1, x);
}
// move the cursor left one postion
void moveleft(){
	getyx(stdscr, y, x);
	move(y, x - 1);
}
// move the cursor right one position
void moveright(){
	getyx(stdscr, y, x);
	move(y, x + 1);
}
// delete the current line
void deleteline(){
	deleteln();
}
// insert a line at the current position
void insertline(){
	getyx(stdscr, y, x);
	insertln();
	move(y + 1, x);
}
// delete the character to the left of the cursor
void backspace(){
	getyx(stdscr, y, x);
	mvdelch(y, x - 1);
}
// insert a character and shift line to the right
void insertchar(char c){
	getyx(stdscr, y, x);
	insch(c);
	move(y, x + 1);
}
// enable command mode
void commandmodeon(){
	getyx(stdscr, y, x);
	move(30, 0);
	deleteline();
	printw("Command Mode: 'I': Enable Insert Mode 'X': Delete Line 'O': Insert Line 'S': Save File");
	move(y, x);
	mode = 'c';
}
// disable command mode
void commandmodeoff(){
	getyx(stdscr, y,x);
	move(30, 0);
	deleteline();
	deleteline();
	printw("Insert Mode:");
	move(y, x);
	mode = 'i';
}
//saves contents of user entered data or prints it out based on arguments
void copyPaste(char choice, int SIZE, char pasted[]){
    if(choice = 'c'){
        printw("Enter text to copy (end with ';'): ");//prompt for copy text

        for(int i = 0; i <= SIZE - 1; i++){
            char input = getch();//get char from user
            if (input == ';' || i == SIZE - 1){//copy stopper
                printw("Copying finished.");
                pasted[i] = ';';//definate semicolon entered
                i = SIZE;//double assurance for falling out of loop
                break;//fall out of loop
            }
            else{
                pasted[i] = input;//char from user entered
            }
        }
    }//copy
    else if(choice = 'p'){
        for(int i = 0; i < SIZE - 1; i++){
            if(pasted[i] == ';'){//check for end line char
                i = SIZE;//double assurance for falling out of loop
                break;//stops at semicolon if you don't use entire array
            }
            else
                insertchar(pasted[i]);
        }//uses insertchar because that's technically happening anyway
    }//paste
    else{
        printw("Error with choice");
    }
}

