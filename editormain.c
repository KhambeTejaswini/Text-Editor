/*****************************************************************************
 * Copyright (C) Khambe Tejaswini Rajaram khambetr15.comp@coep.ac.in
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/
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
        int menu_size = 3;
	char c;
	char *str;
	if(argc == 0){	
		str = NULL;
	}
	else
		str = argv[1];
	initscr();
        noecho();
	keypad(stdscr,TRUE);
        curs_set(TRUE);
	//curses_init();
        getmaxyx(stdscr, parent_y, parent_x);
        WINDOW *filename  = newwin(name_size,parent_x, 0, 0);
	noecho();
        WINDOW *field = newwin(parent_y - menu_size - name_size, parent_x, 1, 0);	
	//scrollok(field,TRUE);
	keypad(field,TRUE);
	keypad(filename,TRUE);
	noecho();
        WINDOW *menu = newwin(menu_size, parent_x, parent_y - menu_size, 0);
	start_color();
	init_pair(1,COLOR_BLACK,COLOR_WHITE);
	init_pair(2,COLOR_WHITE,COLOR_BLACK);
	wbkgd(menu,COLOR_PAIR(2));
	wrefresh(menu);
	wbkgd(filename,COLOR_PAIR(2));
	wrefresh(filename);
	wbkgd(field,COLOR_PAIR(1));
	wrefresh(field);
	keypad(menu,TRUE);
	noecho();
	list *l;
	l = open_file(str);
	getmaxyx(stdscr, new_y, new_x);
	print_menu(menu, 0 , 0);
	wrefresh(menu);
	mvwprintw(filename, 0, new_x/2-9,"FILE NAME : %s" ,str);
	wrefresh(filename);
	edit_win(l,field,menu,filename,str);
	wrefresh(filename);
	wrefresh(field);
	wrefresh(menu);
	delwin(filename);
	delwin(field);
	delwin(menu);
	endwin();
	return 0;
    }

