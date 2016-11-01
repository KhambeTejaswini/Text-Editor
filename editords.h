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

