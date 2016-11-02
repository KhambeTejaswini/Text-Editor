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
