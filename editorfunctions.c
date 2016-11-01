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
	int  y = 0, x = 0,i,k,count=0,x1,y1,x2,y2,flag, new_x,new_y;
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
		getmaxyx(stdscr, new_y, new_x);
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
					if(y == 0&&x!=0){
					x--;
					for(k = 0;k<x;k++)
							p = p->next;
						y = p->line_size-1;
					}
					else if(y == 0&&x==0)
						break;
					else
     		   	                --y;
					colour = 0;
					wrefresh(w);
					wclear(w);
                         		traverse(l,w);
		                	wmove(w, x, y);
                    			break;
                		case KEY_RIGHT :
					for(k = 0;k<x;k++)
						p = p->next;
					if(y == p->line_size-1 && x < l->length-1){
						y = 0;
						x++;
					}
					if(x < l->length&&y<p->line_size){
						if(p->str[y] == '\t')
							y = y +7;
                   				y++;
					}
					colour = 0;
					wrefresh(w);
					wclear(w);
                         		traverse(l,w);
		                	wmove(w, x, y);
                   			break;
                		case KEY_UP:
					/*if(x == 0){
						wscrl(w, -1);
						wprintw(w,"hello");
						wrefresh(w);
					}*/
					if(!x)
                    				break;
					else{
						for(k = 0;k<x-1;k++)
							p = p->next;
						
						if(y == p->next->line_size -1)
							y = p->line_size-1;
						x--;
						
					}
					colour = 0;
					wrefresh(w);
					wclear(w);
                         		traverse(l,w);
		                	wmove(w, x, y);
                    			break;
                		case KEY_DOWN :
					if(x == l->length-1)
						break;
					for(k = 0;k<x;k++)
						p = p->next;
					if(y == p->line_size -1)
						y = p->next->line_size-1;
					if(p->next != NULL)
                    				x++;
					colour = 0;
					wrefresh(w);
					wclear(w);
                         		traverse(l,w);
		                	wmove(w, x, y);
                    			break;
                		case KEY_BACKSPACE :
					if(x == 0&&y== 0){
						init(l);
						break;
					}
					if(y == 0){
						if(x > 0)
							x--;
						for(k = 0;k<x;k++)
							p = p->next;
						y = p->line_size-1;
						
					}
					else if(y > 0){
						y--;
					}
					remov(l,y+1,x);
					wclear(w); 
	           			traverse(l,w);
					wmove(w,x,y);
					colour = 0;
					break;
				case KEY_TAB:
					insert(l,y,x,'\t');
					y = y + 8;
					wrefresh(w);
					wclear(w);
					traverse(l,w);
					colour = 0;	
		                	wmove(w, x, y);
					break;
				case CTRL_D:
					delete_line(l,x);
					if(x)
						x--;
					y = 0;
					wrefresh(w);
					wclear(w);
					traverse(l,w);
		                	wmove(w, x, y);
					colour = 0;	
					break;
				case KEY_SRIGHT:
					if(colour == 0){
						x1 = y;
						y1 = x;
					}
					colour = 1;
					mvwchgat(w,x,y, 1, A_BOLD, COLOR_PAIR(2), NULL);
					wrefresh(w);
					for(k = 0;k<x;k++)
						p = p->next;
					if(y == p->line_size-1 && x < l->length-1){
						y = 0;
						x++;
					}
					else if(x < l->length&&y<p->line_size){
						if(p->str[y] == '\t')
							y = y +7;
                   				y++;
					}
					x2 = y;
					y2 = x;
		                	wmove(w, x, y);
                   			break;	
				case KEY_SLEFT:
					if(y == 0 && x == 0)
						break;
					if(y == 0&&x!=0){
						x--;
						for(k = 0;k<x;k++)
							p = p->next;
							y = p->line_size-1;
					}
					else
     		   	                	--y;
					if(colour == 0){
						x2 = y;
						y2 = x;
					}
					colour = 1;
					mvwchgat(w,x,y,1, A_BOLD,COLOR_PAIR(2), NULL);
					wrefresh(w);
					x1 = y;
					y1 = x;
		                	wmove(w, x, y);
					break;
				case CTRL_B:
					if(colour == 1)
					str = copy(l, x1, y1,x2 ,y2, w);
		                	wmove(w, x, y);
					break;
				case CTRL_V:
					paste(l, str,y, x);
					wclear(w);
					wrefresh(w);
					traverse(l,w);
					wmove(w, x + x2 - x1, y + y2 - y1);	
					break;	
				case CTRL_X:
					if(colour == 1){
						str = cut(l,x1,y1,x2,y2,w);
						wmove(w,x1,y1);
						wclear(w);
						wrefresh(w);
						traverse(l,w);
					}
					y = x1;
					x = y1;
					wmove(w,y1,x1);
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
				print_menu(menu, y ,x);
  		    		wrefresh(w);
        	}
        else if((ch == '\n') || (ch > 31 && ch < 127)){
		if(ch == '\n'){
			insert(l,y,x,ch);
			x++;
			y = 0;
			wclear(w);
			traverse(l,w);
			wmove(w,x,y);
		}
                else{
			insert(l,y,x,ch);
			count++;
   	                y++;
	    		wrefresh(w);
	                wclear(w);
        	        traverse(l,w);
			print_menu(menu,y,x);
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

