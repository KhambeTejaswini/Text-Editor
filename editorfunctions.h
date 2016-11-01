#ifndef __EDITORFUNCTIONS_H
#define __EDITORFUNCTIONS_H
#include<ncurses.h>
#include"editords.h"
#define CTRL_W 23 //save file
#define CTRL_O 15 // open file
#define CTRL_E 5 //exit from editor
#define CTRL_D 4 // delete line
#define KEY_TAB 9 // tab
#define CTRL_R 18 //replace a string with other
#define CTRL_X 24 //cut 
#define CTRL_V 22 //paste
#define CTRL_B 2 //copy
void edit_win(list* ,WINDOW* ,WINDOW*, WINDOW* ,char*);
void print_menu(WINDOW*,int,int);
#endif
