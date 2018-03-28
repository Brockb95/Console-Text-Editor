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

void searchReplace(const char* str,const char* old, const char* new){
    FILE *original, *temp;
    char choice;
    if(choice == 'R'){

    	if((original = fopen(str, "r")) == NULL){
        perror(str);
        exit(1);
    }

    if((temp = fopen("temp.txt", "w")) == NULL){
        perror("text");
        exit(1);
    }

    const int BUFFER_SIZE = fsize(str);
    char *buffer = malloc(BUFFER_SIZE);
    char *init_loc = buffer;

    int word_len = strlen(old);
    int counter = 0;

    while(fgets(buffer, BUFFER_SIZE, original)){
        while((buffer = strstr(buffer, old))){
            memcpy(buffer, new, word_len);
            counter++;
        }
        buffer = init_loc;
        fprintf(temp, "%s", buffer);
    }
    printf("'%s' found %i times\n", old, counter);

    fclose(original);
    fclose(temp);

    if((original = fopen(str, "w")) == NULL){
        perror(str);
        exit(1);
    }

    if((temp = fopen("temp.txt", "r")) == NULL){
        perror("text");
        exit(1);
    }

    int c;
    while((c = fgetc(temp)) != EOF){
        fputc(c, original);
    }
}

    fclose(original);
    fclose(temp);
    free(buffer);

}	

int fsize(const char *str){
    FILE *f;
    if((f = fopen(str, "r")) == NULL){
        perror(str);
        exit(1);
    }
    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    fclose(f);
    return size;
}

void write_to_file(const char *str){
    FILE *in;
    char choice;
    if (choice == 'W'){
    if((in = fopen(str, "w")) == NULL){
        perror(str);
        exit(1);
    }
    int c;
    while((c = getchar()) != EOF){
        fputc(c, in);
    }
}
    fclose(in);
}

