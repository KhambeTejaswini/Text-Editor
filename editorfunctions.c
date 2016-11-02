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
#include<stdio.h>
#include<ncurses.h>
#include<stdlib.h>
#include<unistd.h>
#include"editorfunctions.h"
#include"editords.h"
//#define CTRL_W 23
void edit_win(list* l,WINDOW *w, WINDOW *menu, WINDOW *filename, char * file_name) {
	curs_set(TRUE);
	wrefresh(w);
	wclear(w);
	traverse(l,w);
	int ch;
	char c;
	char *str;
	char orig[10], new[10];
	int  y = 0, x = 0,i,k,x1,y1,x2,y2,flag, new_x,a = 0,b = 0;
	//int parent_x,parent_y;
	//getmaxyx(stdscr, parent_y, parent_x);
	//int name_size = 1;
	//int menu_size = 3;
	wmove(w,y,x);
	print_menu(menu, y ,x);
	node* p;
	int colour = 0;
	flag = 0;
        while((ch = wgetch(w))) {
		new_x = getmaxx(w);
        /*	if (new_y != parent_y || new_x != parent_x) {
			parent_x = new_x;
			parent_y = new_y;
			wresize(filename,name_size,new_x);
			wresize(w, new_y - menu_size - name_size, new_x);
			wresize(menu, menu_size, new_x);	
			mvwin(w,name_size,0);
			mvwin(menu, new_y - menu_size, 0);
			wclear(stdscr);
			wclear(filename);
			wclear(w);
			wclear(menu);
        	}
		print_menu(menu, 0 , 0);
		wrefresh(menu);
		mvwprintw(filename, 0, new_x/2-9,"FILE NAME : %s" ,str);
		wrefresh(filename);*/
		p = l->head;
		i = 0;
        	if(ch == KEY_LEFT || ch == KEY_RIGHT || ch == KEY_UP || ch == KEY_DOWN || ch == KEY_BACKSPACE || ch == KEY_TAB || ch == CTRL_D || ch == KEY_SRIGHT ||ch == KEY_SLEFT || ch == CTRL_R || ch == CTRL_B || ch == CTRL_V || ch == CTRL_X || ch == CTRL_W || ch == CTRL_E ||ch == CTRL_O){
        		switch(ch) {
      	 	  	        case KEY_LEFT :
					if(a <= 0 && b <= 0)
						break;
					if(y == 0&&x!=0)
						x--;
					for(k = 0;k < b-1;k++)
						p = p->next;
					if(a == 0 ){
						y = (p->line_size-1) % getmaxx(w);
						b--;
						a = p->line_size-1;
					}
					else if(y == 0){
						y = getmaxx(w) - 1;
						a--;
					}
					else{
						if(p->next->str[a-1] == '\t')
							y = y - 7;
						a--;
     		   	                	y--;
					}
					colour = 0;
					wrefresh(w);
					wclear(w);
                         		traverse(l,w);
		                	wmove(w, x, y);
                    			break;
                		case KEY_RIGHT :
					if(l->length == 0)
						break;
					for(k = 0;k<b;k++)
						p = p->next;
					if( (b >= (l->length - 1)) && (a >= p->line_size  ))
						break;
					if(a == p->line_size-1 && b < l->length-1){
						b++;
						a = 0;
						y = 0;
						x++;
					}
					else if((y == getmaxx(w) - 1) && a < p->line_size){
						y = 0;
						x++;
						a++;
					}
					else {
						if(p->str[a] == '\t'){
							y = y + 7;
						}
						a++;
                   				y++;
					}
					colour = 0;
					wrefresh(w);
					wclear(w);
                         		traverse(l,w);
		                	wmove(w, x, y);
                   			break;
                		case KEY_UP:
					if(!x)
                    				break;
					for(k = 0;k<b-1;k++)
							p = p->next;
					if(a > getmaxx(w)){
						a = a - getmaxx(w);
						x--;
					}
					else{
						if(a > (p->line_size % getmaxx(w))){
							a = p->line_size -1;
							y = a % getmaxx(w);
						}
						else{
							a = (p->line_size / getmaxx(w)) *getmaxx(w) + a;
						}
						b--;
						x--;

					}
					
					colour = 0;
					wrefresh(w);
					wclear(w);
                         		traverse(l,w);
		                	wmove(w, x, y);
                    			break;
                		case KEY_DOWN :
					for(k = 0;k<b;k++)
						p = p->next;
					if((b >= l->length-1))
						break;
					if((a == p->line_size) && (p->next->line_size < y)){
						y = p->next->line_size;
						a = y;
						b++;
						x++;
					}
					else if(a >= ((p->line_size)/new_x)*new_x ){
                    				b++;
						x++;
						a = a % new_x;
					}	
					else{
						a = a + new_x;
						x++;
					}
					colour = 0;
					wrefresh(w);
					wclear(w);
                         		traverse(l,w);
		                	wmove(w, x, y);
                    			break;
                		case KEY_BACKSPACE :
					if(x == 0 && y == 0)
						break;
					if(y == 0&&x!=0)
						x--;
						for(k = 0;k < b-1;k++)
							p = p->next;
						if(a == 0 ){
							y = (p->line_size-1) % getmaxx(w);
							b--;
							a = p->line_size-1;
						}
						else if(y == 0){
							y = getmaxx(w) - 1;
							a--;
						}
					else{
						if(p->next->str[a-1] == '\t')
							y = y - 7;
						a--;
     		   	                	y--;
					}
					remov(l,a+1,b);
					wclear(w); 
	           			traverse(l,w);
					wmove(w,x,y);
					colour = 0;
					break;
				case KEY_TAB:
					insert(l,y,x,'\t');
					y = y + 8;
					a++;
					wrefresh(w);
					wclear(w);
					traverse(l,w);
					colour = 0;	
		                	wmove(w, x, y);
					break;
				case CTRL_D:
					delete_line(l,x);
					if(x){
						for(k = 0;k < b;k++)
							p = p->next;
						x = x - (p->line_size/new_x) - 1;
						b--;
					}
					y = 0;
					a = 0;
					wrefresh(w);
					wclear(w);
					traverse(l,w);
		                	wmove(w, x, y);
					colour = 0;	
					break;
				case KEY_SRIGHT:
					if(colour == 0){
						x1 = a;
						y1 = b;
					}
					colour = 1;
					mvwchgat(w,x,y, 1, A_BOLD, COLOR_PAIR(2), NULL);
					wrefresh(w);
					for(k = 0;k<b;k++)
						p = p->next;
					if( (b == l->length - 1) && (a == p->line_size  ))
						break;
					if(a == p->line_size-1 && b < l->length-1){
						b++;
						a = 0;
						y = 0;
						x++;
					}
					else if((y == getmaxx(w) - 1) && a < p->line_size){
						y = 0;
						x++;
						a++;
					}
					else {
						if(p->str[y] == '\t'){
							y = y + 7;
						}
						a++;
                   				y++;
					}
					
					x2 = a;
					y2 = b;
		                	wmove(w, x, y);
                   			break;	
				case KEY_SLEFT:
					if(a <= 0 && b <= 0)
						break;
					if(y == 0 && x!=0)
						x--;
						for(k = 0;k < b-1;k++)
							p = p->next;
						if(a == 0 ){
							y = (p->line_size-1) % getmaxx(w);
							b--;
							a = p->line_size-1;
						}
						else if(y == 0){
							y = getmaxx(w) - 1;
							a--;
						}
					else{
						a--;
     		   	                	y--;
					}
					if(colour == 0){
						x2 = a;
						y2 = b;
					}
					colour = 1;
					mvwchgat(w,x,y,1, A_BOLD,COLOR_PAIR(2), NULL);
					wrefresh(w);
					x1 = a;
					y1 = b;
		                	wmove(w, x, y);
					break;
				case CTRL_B:
					if(colour == 1)
					str = copy(l, x1, y1,x2 ,y2, w);
		                	wmove(w, x, y);
					break;
				case CTRL_V:
					paste(l, str,a, b);
					wclear(w);
					wrefresh(w);
					traverse(l,w);
					wmove(w, x ,y);	
					break;	
				case CTRL_X:
					if(colour == 1){
						str = cut(l,x1,y1,x2,y2,w);
						wclear(w);
						wrefresh(w);
						traverse(l,w);
					}
					//y = x1 % new_x;
					//x = y1;
					wmove(w,x,y);
					wrefresh(w);
					break;
				case CTRL_R:
					wclear(menu);
					mvwprintw(menu,0,0,"Enter string to be replaced:");
					wrefresh(menu);
					i = 0;
					while((c = wgetch(menu)) != '\n'){
						mvwprintw(menu,0,i + 28,"%c",c);
						orig[i] = c;
						i++; 
					}
					orig[i] = '\0';
					mvwprintw(menu,0,getmaxx(menu)/2,"Enter new string:");
					wrefresh(menu);
					i = 0;
					while((c = wgetch(menu)) != '\n'){
						mvwprintw(menu,0,getmaxx(menu)/2+i+18,"%c",c);
						new[i] = c;
						i++; 
					}
					new[i] = '\0';
					wrefresh(menu);
					if(stringreplace(w,menu,l,orig,new)){				
						wclear(menu);
						mvwprintw(menu,0,0,"No string found");
						wrefresh(menu);
					}
					
					wclear(menu);
					wrefresh(menu);
					wclear(w);
					wrefresh(w);
					traverse(l,w);
					wmove(w, y ,x);
					break;
				case CTRL_O:
					mvwprintw(menu,0,0,"Enter new filename:");
					wrefresh(menu);
					i = 0;
					while((c = wgetch(menu)) != '\n'){
						mvwprintw(menu,0,i+25,"%c",c);
						new[i] = c;
						i++; 
					}
					new[i] = '\0';
					l = open_file(new);
					wclear(filename);
					mvwprintw(filename, 0, new_x/2-9,"FILE NAME : %s" ,new);
					wrefresh(filename);
					wclear(w);
					wrefresh(w);
					traverse(l,w);
					wmove(w, 0, 0);
					break;
				case CTRL_W:
					save_file(l, file_name,menu,filename);
					flag = 1;
					break;
				case CTRL_E:
					if(flag == 0){
						wclear(menu);
						mvwprintw(menu,0,0, "changes in file not saved, save ? : y/n");
						c = wgetch(menu);
						if(c == 'y' || c == 'Y')
						save_file(l, file_name,menu,filename);
					}
					endwin();
					exit(1);
			} 
				print_menu(menu, a ,b);
  		    		wrefresh(w);
        	}
        else if((ch == '\n') || (ch > 31 && ch < 127)){
		if(ch == '\n'){
			insert(l,a,b,ch);
			b++;
			x++;
			y = 0;
			a = 0;
			wclear(w);
			traverse(l,w);
			wmove(w,x,y);

		}
                else{
			if(y == getmaxx(w)){
				y = 0;
				x++;
			}
			insert(l,a,b,ch);
   	                y++;
			a++;
	    		wrefresh(w);
	                wclear(w);
        	        traverse(l,w);
			print_menu(menu,a,b);
			wmove(w,x,y);
			wrefresh(w);
		}
        }
    }
	wrefresh(w);
}
void print_menu(WINDOW *menu, int y,int x){
	int maxx = getmaxx(menu);
	mvwprintw(menu,1,0     ,"OPEN    :^o");
	mvwprintw(menu,1,maxx/4,"SAVE    :^w");
	mvwprintw(menu,1,maxx/2,"EXIT    :^e");
	mvwprintw(menu,1,3*maxx/4,"REPLACE    :^r");
	mvwprintw(menu,2,0     ,"CUT     :^x");
	mvwprintw(menu,2,maxx/4,"COPY    :^b");
	mvwprintw(menu,2,maxx/2,"PASTE   :^v");
	mvwprintw(menu,2,3*maxx/4,"DELETELINE :^d");
	mvwprintw(menu,0,maxx -16,"Ln%3d,Col%3d",y,x);
	wrefresh(menu);
//	wprintw(menu,"save:^S\t");
//	wprintw(menu,"save:^S\t");	

}

