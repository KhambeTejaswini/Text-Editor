#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"editords.h"
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
	if( y == l->length && x==0){
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
	int i = 0 , j = 0,k = 0;
	node *p,*tmp;
	p = l->head;
	while(j<y){
		p = p->next;
		j++;
	}
	k = x-1;
	if(p->str[x] == '\n'){
		while(i < p->next->line_size){
			p->str[p->line_size+i-1]=p->next->str[i];
			i++;
		}
		p->line_size = p->line_size + i;
		tmp = p->next;
		p->next = p->next->next;
		//free(tmp->str);
		free(tmp);
		l->length--;
		/*if(l->length == 0)
			init(l);*/
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
	//wprintw(w,"hello");
	node *p = l->head;
	//FILE *f;
	//f = fopen("anusha","w");
	int x;
	while(p != NULL) {
		//wprintw(w,"%d",y);
		for(x = 0; x < p->line_size ; x++)
			wprintw(w,"%c", p->str[x]);
		//y++;

		p = p->next;
	}  
	return;
}
list* open_file(char* s){
	FILE* f1;
	list *l;
	l = (list*)malloc(sizeof(list));
	init(l);
	f1 = fopen(s,"r");
	char c;
	int i = 0,j=0;
	int m;
	do{
		i = 0;
		do{
			m = fscanf(f1,"%c",&c);
			//wprintw(w,"%c",c);
			insert(l,i,j,c);
			i++;
		}while(c != '\n'&& m != EOF);
		j++;
	}while(m != EOF);
	fclose(f1);
	return l;
	
}
void save_file(list *l,char *filename){
	FILE *f1;
	f1 = fopen(filename,"w");
	//char c;
	int x;
	node* p;
	p = l->head;
	do {
		for(x = 0; x < p->line_size ; x++)
			fprintf(f1,"%c", p->str[x]);
		p = p->next;
	} while(p != NULL) ;
	return;
}
/*char* copy(list* l,int x1,int y1, int x2, int y2){
	int i = 0, j = 0;
	list *p;
	char *tmp;
	int l = (y2-y1)*getmaxx(w) + x2-x1;
	tmp = (char*)malloc(sizeof(char)*l);
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
	}while(x1 != x2 && y1 != y2)
	tmp[j] = '\0';
	return tmp;
}
char* cut(list* ,int x1,int y1,int x2,int y2){
	int i = 0, j = 0;
	list *p;
	char *tmp;
	int l = (y2-y1)*getmaxx(w) + x2-x1;
	tmp = (char*)malloc(sizeof(char)*l);
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
	}while(x1 != x2 && y1 != y2)
	tmp[j] = '\0';
	return tmp;

}

*/
