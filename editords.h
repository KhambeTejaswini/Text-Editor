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
#ifndef __EDITORDS_H
#define __EDITORDS_H
#include<ncurses.h>
typedef struct node{
        char* str;
        struct node *next;
	int line_size;
} node;
typedef struct list{
        node *head;
        int length;
}list;
void init(list*);
int insert(list* ,int ,int ,char);
void remov(list*,int, int);
void traverse(list* l,WINDOW*);
void save_file(list* l,char* c,WINDOW* ,WINDOW* );
list* open_file(char* );
void delete_line(list* ,int);
char* copy(list*,int ,int ,int ,int, WINDOW* );
char* cut(list* ,int ,int, int, int, WINDOW*);
void paste(list* ,char*,int ,int );
int stringreplace(WINDOW* ,WINDOW* ,list*, char *orig, char *new);
#endif

