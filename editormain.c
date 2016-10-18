#include <ncurses.h> 
#include<stdio.h>
#include<string.h>
#include <unistd.h>
#include<stdlib.h>
#include "editorfunctions.h"
#include "editords.h"
int main(int argc, char *argv[]) {
	int parent_x, parent_y,new_y,new_x;
        int name_size = 1;
        int menu_size = 2;
	int ch;
	char *str;
	str = (char*)malloc(16);
	strcpy(str,argv[1]);
        initscr();
        noecho();
	//cbreak;
	keypad(stdscr,TRUE);
        curs_set(TRUE);
    // get our maximum window dimensions
        getmaxyx(stdscr, parent_y, parent_x);
    // set up initial windows
        WINDOW *filename  = newwin(name_size,parent_x, 0, 0);
	noecho();
        WINDOW *field = newwin(parent_y - menu_size - name_size, parent_x, 1, 0);	
	keypad(field,TRUE);
	keypad(filename,TRUE);
	noecho();
        WINDOW *menu = newwin(menu_size, parent_x, parent_y - menu_size, 0);
	print_menu(menu , parent_y - menu_size, parent_y);
	wgetch(menu);
	noecho();
        FILE* f1 = fopen(argv[1],"a");
	list *l;
	//wprintw(field, "hello");
	/*if(argc < 1){
		//wprintw(field, "hello");
		l = (list*)malloc(sizeof(list));
		init(l);
		strcpy(str,"NO NAME");
	}
	else{
		//wprintw(field, "hello");
		str = argv[1];
		l = open_file(str);
	}*/
	while(1){    
        	getmaxyx(stdscr, new_y, new_x);
        	if (new_y != parent_y || new_x != parent_x) {
			parent_x = new_x;
			parent_y = new_y;
			wresize(filename,name_size,new_x);
			wresize(field, new_y - menu_size - name_size, new_x);
			wresize(menu, menu_size, new_x);	
			mvwin(field,name_size,0);
			mvwin(menu, new_y - menu_size, 0);
				//print_menu(menu , new_x, new_y);
			wclear(stdscr);
			wclear(filename);
			wclear(field);
			wclear(menu);
        	}
		
		mvwprintw(filename, 0, parent_x/2-9,"FILE NAME : %s" ,str);
		wgetch(filename);
		l = open_file(str);
		//traverse(l,field);
		edit_win(l,field);
		save_file(l,str);
		ch = wgetch(filename);
		if(ch == CTRL_E)
			exit(1);
		wrefresh(filename);
		wrefresh(field);
		wrefresh(menu);
       }
  //  sleep(50000); // clean up
    delwin(filename);
    delwin(field);
    delwin(menu);
    endwin();
    return 0;
    }

