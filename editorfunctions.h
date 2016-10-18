#include<ncurses.h>
#include"editords.h"
#define CTRL_W 23
#define CTRL_O 15
#define CTRL_E 5
#define CTRL_I 9
void edit_win(list* ,WINDOW*);
void print_menu(WINDOW*,int,int);
//list* open_file(char*);
