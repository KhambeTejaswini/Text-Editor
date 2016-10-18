#include<stdio.h>
#include<ncurses.h>
#include<stdlib.h>
#include"editorfunctions.h"
#include"editords.h"
//#define CTRL_W 23
void edit_win(list* l,WINDOW *w) {
	curs_set(TRUE);
	wrefresh(w);
	wclear(w);
	traverse(l,w);
	//sleep(100000);
	int ch;
	//list *l;
	//l = (list*)malloc(sizeof(list));
	int  y = 0, x = 0,k,count=0;
	node* p;
	 
        while(((ch = wgetch(w))!= CTRL_W )&&(ch != CTRL_E )) {
        	//traverse(l,w);
		
		p = l->head;
        	if(ch == KEY_LEFT || ch == KEY_RIGHT || ch == KEY_UP || ch == KEY_DOWN || ch == KEY_BACKSPACE ) {
        		switch(ch) {
      	 	  	        case KEY_LEFT :
					if(y == 0&&x!=0){
					x--;
					for(k = 0;k<x;k++)
							p = p->next;
						y = p->line_size-1;
					}
					else
     		   	                --y;
					//--m;
                    			break;
                		case KEY_RIGHT :
					for(k = 0;k<x;k++)
						p = p->next;
					if(y == p->line_size-1){
						y = 0;
						x++;
					}
					else if(x <= l->length)
                   				y++;
                   			break;
                		case KEY_UP:
					for(k = 0;k<x-1;k++)
						p = p->next;
					if(y == p->next->line_size -1)
						y = p->line_size-1;
                    			x--;
                    			break;
                		case KEY_DOWN :
					for(k = 0;k<x;k++)
						p = p->next;
					if(y == p->line_size -1)
						y = p->next->line_size-1;
					if(x < l->length-1)
                    				x++;
					//m = m + getmaxy(w);
                    			break;
                		case KEY_BACKSPACE :
					if(y == 0){
						x--;
						for(k = 0;k<x;k++)
							p = p->next;
						y = p->line_size-1;
					}
					else 
						y--;
					remov(l,y+1,x); 
					count--;
					wrefresh(w);
					wclear(w);
                         		traverse(l,w);
					break;
				//case KEY_TAB:
				  //      y = y + 8;
					//break;
		            
			} 
			//if(y+x*getmaxy(w)<=count){
	                	wmove(w, x, y);
  		    		wrefresh(w);
			//}
            
        	}
            
        
        else {
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
		   // fprintf(f,"%c",ch);
   	                y++;
		/*	if(y==getmaxy(w)){
				y=0;
				x++;
			}*/
        	        //m++;
	    		wrefresh(w);
	                wclear(w);
        	        traverse(l,w);
			//if(y+x*getmaxy(w)<=count){
				wmove(w,x,y);
				wrefresh(w);
			//}
		}
        }
     
    }
    wrefresh(w);
	//fclose(f);

}


void print_menu(WINDOW *menu,int y, int maxx){
	wprintw(menu,"save:^W\t");
	wprintw(menu ,"open:^O\t");
	wprintw(menu, "EXIT:^E\t");
	wprintw(menu, "INSERT:^I\t");
	//wprintw(menu,"save:^S\t");
	//wprintw(menu,"save:^S\t");	

}

