#include <ncurses.h>
#define MAX 3200
#define MAX_ROW_EDIT 50
#define MAX_COL_EDIT 80

typedef struct buffer {
	char text[MAX];
	int row;
	int col;
}buff;

