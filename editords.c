#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"editords.h"
#include"editorfunctions.h"
#include<ncurses.h>
#define MAX 128
void init(list *l){
	l->head = NULL;
	l->length = 0;
}
int insert(list *l,int x,int y,char c){
	if(y < 0 || y > l->length)
		return 0;
	int j = 0,k ;
	node *p;
	p = l->head;
	if( y == l->length && x == 0){
		l->length++;
		node *tmp;
		tmp = (node*)malloc(sizeof(node));
		tmp->line_size = 0;
		tmp->str = (char*)malloc(sizeof(char)*MAX);
		tmp->next = NULL;
		if(l->head == NULL){
			l->head = tmp;
		}
		else{
			while(j < y-1){
				p = p->next;
				j++;	
			}
			p->next = tmp;
		}
		tmp->str[x] = c;
		tmp->line_size++;
		return 1;
	}
	else{	
		p = l->head;
		j = 0; 
		while(j < y){
			p = p->next;
			j++;	
		}
		if(c == '\n'){
			l->length++;
			node *tmp;
			tmp = (node*)malloc(sizeof(node));
			tmp->line_size = 0;
			tmp->str = (char*)malloc(sizeof(char)*MAX);
			tmp->next = p->next;
			k = x;
			int s = 0 ;
			int m = p->line_size;
			if(x < p->line_size){
				while(k < m){
					tmp->str[s] = p->str[k];
					k++;
					s++;
					p->line_size--;
					tmp->line_size++; 	
				}
				//tmp->str[s] = '\n';
				tmp->line_size++;
			}
			p->str[x] = '\n';
			p->line_size++;
			p->next = tmp;
			return 1;
		}
		if(x < 0 || x > p->line_size)
			return 0;
		k = p->line_size -1;
		if(x < p->line_size){
			while(k >= x){
				p->str[k+1] = p->str[k];
				k--; 	
			}		
		}
		p->str[x] = c;	
		p->line_size++;
		if(p->line_size % 128 == 0){
			p->str = (char*)realloc(p->str,(p->line_size) * 2);
		}
		return 1;
	}
}
void remov(list* l,int x,int y){
	if(x < 0||y < 0)
		return;
	int i = 0 , j = 0,k = 0;
	node *p,*tmp;
	p = l->head;
	if(x == 0&&y == 0){
		l->head = l->head->next;
		free(p->str);
		free(p);
		init(l);
		return;
	}
	while(j<y){
		p = p->next;
		j++;
	}
	k = x-1;
	if(p->str[x] == '\n'){
		while(i < p->next->line_size){
			p->str[p->line_size+i-1] = p->next->str[i];
			i++;
		}
		p->line_size = p->line_size + i;
		tmp = p->next;
		p->next = p->next->next;
		free(tmp);
		l->length--;
		return;
	}
	while(k<p->line_size){
		p->str[k] = p->str[k+1];
		k++;
	}
	p->line_size--;
	if(p == l->head && p->line_size == 0){
		free(l->head->str);
		free(l->head);
		init(l);
	}
}
void traverse(list *l,WINDOW* w){
	node *p = l->head;
	int x;
	while(p != NULL) {
		for(x = 0; x < p->line_size ; x++)
			wprintw(w,"%c", p->str[x]);
		p = p->next;
	}  
	return;
}
list* open_file(char* s){
	list *l1;
	l1 = (list*)malloc(sizeof(list));
	init(l1);
	if(s == NULL)
		return l1;
	FILE* f1;
	if((f1 = fopen(s,"r")) == NULL){
		f1 = fopen(s,"a");
		return l1;
	}
	char c;
	int i = 0,j=0;
	int m;
	do{
		i = 0;
		do{
			m = fscanf(f1,"%c",&c);
			insert(l1,i,j,c);
			i++;
		}while(c != '\n'&& m != EOF);
		j++;
	}while(m != EOF);
	fclose(f1);
	return l1;
	
}
void save_file(list *l,char *file_name,WINDOW* menu,WINDOW* filename){
	char c;
	FILE *f1;
	int new_x,i;
	new_x = getmaxx(filename);
	if(file_name == NULL){
		file_name = (char*)malloc(20);
		wclear(menu);
		wprintw(menu,"Enter file_name :");
		print_menu(menu,0,0);
		while((c = wgetch(menu)) != '\n'){
			mvwprintw(menu,0,i+19,"%c",c);
			file_name[i] = c;
			i++; 
		}
		file_name[i] = '\0';
	}
	f1 = fopen(file_name,"w");
	int x;
	node* p;
	p = l->head;
	do {
		for(x = 0; x < p->line_size ; x++)
			fprintf(f1,"%c", p->str[x]);
		p = p->next;
	} while(p != NULL) ;	
	wclear(filename);
	mvwprintw(filename, 0, new_x/2-9,"FILE NAME : %s" ,file_name);
	wrefresh(filename);
	wclear(menu);
	print_menu(menu,0,0);
	return;
}
void delete_line(list* l,int x){
	node* p = l->head;
	if(x == 0){
		l->head = p->next;
		free(p->str);
		free(p);
		l->length--;
		return;
	}
	int i ;
	for( i =0 ; i < x-1;i++)
		p = p->next;
	node *tmp = p->next;
	p->next = p->next->next;
	free(tmp->str);
	free(tmp);
	l->length--;	
}
char* copy(list* l,int x1,int y1, int x2, int y2,WINDOW* w){
	int i = 0, j = 0;
	node *p;
	char *tmp;
	int len = (y2-y1)*getmaxx(w) + x2-x1;
	tmp = (char*)malloc(sizeof(char)*(len+1));
	p = l->head;
	for(i = 0;i < y1;i++)
		p = p->next;
	do{
		tmp[j] = p->str[x1];
		if(p->str[x1] == '\n'){
			y1++;
			x1 = 0;
			p = p->next;		
		}
		else
			x1++;
		j++;
	}while(x1 != x2 || y1 != y2);
	tmp[j++] = p->str[x1];
	tmp[j] = '\0';
	return tmp;
}
char* cut(list* l,int x1,int y1,int x2,int y2, WINDOW* w){
	int i = 0, j = 0;
	int k = x1,m = y1;
	node *p;
	char *tmp;
	int len = (y2-y1)*getmaxx(w) + x2-x1;
	tmp = (char*)malloc(sizeof(char)*(len+1));
	p = l->head;
	for(i = 0;i < y1;i++)
		p = p->next;
	do{
		tmp[j] = p->str[k];
		if(p->str[k] == '\n'){
			m++;
			k = 0;
			p = p->next;		
		}
		else
			k++;
		j++;
	}while(k != x2 || m != y2);
	tmp[j++] = p->str[k];
	tmp[j] = '\0';
	k = x2;
	m = y2;
	i = 0;
	do{
		if(k == 0){
			if(m > 0)
				m--;
			for(j = 0;j<m;j++)
				p = p->next;
			k = p->line_size-1;
		}
		else if(k > 0)
			k--;
		remov(l,k+1,m); 
	}while(k != x1 || m != y1);
	remov(l,k+1,m);	
	//remov(l,k,y1);
	//remov(l,k,y1);
	return tmp;
}
void paste(list* l, char* s, int x, int y){
	int i = 0;	
	while(s[i] != '\0'){
		insert(l,x,y,s[i]);
			x++;
		if(s[i] == '\n'){
			y++;
			x = 0;	
			l->length++;
		}	
		i++;	
	}
}

int stringreplace(WINDOW* w,WINDOW* menu,list *l, char *orig, char *new){
	int   i=0, j, k,no=0,lt,lo,ln, count = 0;
	node *p; 
	p = l->head;
	int len = 0;
	char c;
	while(p != NULL){
	lt = strlen(p->str);
	lo = strlen(orig);
	ln = strlen(new);
	for(i = 0; i < (lt+no*(ln-lo)) ;i++ ) {
		if(p->str[i] == orig[0]) {
			count ++;
			for(j = (i + 1), k = 1; k < lo; k++, j++) {
				if(p->str[j] == orig[k])
					count++;
				else
					break;
			}
			if(count == lo){
				mvwchgat(w,len,i,lo,A_BOLD,2,NULL);
				wmove(w,len,i);
				wrefresh(w);
				wrefresh(menu);
				mvwprintw(menu,0,0,"Do you want to replace ? y/n :");
				c = wgetch(menu);
				wprintw(menu,"%c",c);
				wrefresh(menu);
				if(c == 'y'){
				if(ln>lo){
					for(k=lt+no*(ln-lo);k>=i;k--)
						p->str[k+ln-lo] = p->str[k]; 
				}
				if(ln<lo){
					for(k=i;k<lt-no;k++)
						p->str[k] = p->str[k+lo-ln];
				}
				for(k=0;k<ln;k++)
					p->str[i+k]=new[k];
				}
				wclear(w);
				traverse(l,w);
				wrefresh(w);
				no++;
				i=i+ln-1;
			}
		}
		count = 0;
		}
		len++;
		p = p->next;
	}
	return no;
		
}
