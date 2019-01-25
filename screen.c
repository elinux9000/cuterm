#include <stdlib.h>
#include <ncurses.h>			/* ncurses.h includes stdio.h */
#include <string.h>
#include <menu.h>
#include <panel.h>
#include "my_menu.h"

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
int print_top_item(MY_MENU *menu);
void print_all_items(MY_MENU *m);
int main1()
{
	char mesg[]="Just a string";		/* message to be appeared on the screen */
	int row,col;				/* to store the number of rows and *
					 * the number of colums of the screen */
	initscr();				/* start the curses mode */
	getmaxyx(stdscr,row,col);		/* get the number of rows and columns */
	mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);
	/* print the message at the center of the screen */
	mvprintw(row-2,0,"This screen has %d rows and %d columns\n",row,col);
	printw("Try resizing your window(if possible) and then run this program again");
	refresh();
	getch();
	endwin();

	return 0;
}


#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

char *choices[] = {
                        "Choice 1",
                        "Choice 2",
                        "Choice 3",
                        "Choice 4",
                        "Exit",
                        (char *)NULL,
                  };

void print_menu_title(MY_MENU *m)
{
	if (m->win) {
		delwin(m->win);
		m->win = NULL;
	}
	m->win = newwin(3,m->box.width,m->box.y,m->box.x);
	box(m->win, 0, 0);
	if (m->panel)
		replace_panel(m->panel,m->win);
	else
		m->panel = new_panel(m->win);
	print_top_item(m);

}
void print_menu_all(MY_MENU *m)
{
	if (m->win) {
		delwin(m->win);
		m->win = NULL;
	}
	m->win = newwin(m->box.height,m->box.width,m->box.y,m->box.x);
	box(m->win, 0, 0);
	if (m->panel)
		replace_panel(m->panel,m->win);
	else
		m->panel = new_panel(m->win);
	print_all_items(m);
}
void print_all_items(MY_MENU *m)
{
	for (int j=0;strlen(m->menu_items[j])>0;j++) {
		int x;
		if (j == 0) {
			print_top_item(m);
		}
		else {
			x=2;
			mvwprintw(m->win,1+j,x,m->menu_items[j]);
		}
	}
	update_panels();
	doupdate();
}
void create_window_top(MY_MENU *m)
{
	m->win = newwin(3,m->box.width,m->box.y,m->box.x);
}
void create_window_all(MY_MENU *m)
{
	m->win = newwin(m->box.height,m->box.width,m->box.y,m->box.x);
}
int create_panel_all(MY_MENU *menu)
{
	box(menu->win, 0, 0);
	menu->panel = new_panel(menu->win);

	for (int j=0;strlen(menu->menu_items[j])>0;j++) {
		int x;
		if (j == 0) {
			x=1;
		}
		else
			x=2;
		mvwprintw(menu->win,1+j,x,menu->menu_items[j]);
	}
	return EXIT_SUCCESS;
}
int print_top_item(MY_MENU *menu)
{
	wattron(menu->win,A_BOLD);
	mvwprintw(menu->win,1,1,menu->menu_items[0]);
	mvwchgat(menu->win,1,1,1,A_BOLD|A_UNDERLINE,1,NULL);
	return EXIT_SUCCESS;
}
int create_panel_top(MY_MENU *menu)
{
	box(menu->win, 0, 0);
	menu->panel = new_panel(menu->win);
	print_top_item(menu);
	return EXIT_SUCCESS;
}
unsigned count_items(char *list[])
{
	unsigned j;
	for (j=0;strlen(list[j])>0 && j<MAX_MENU_ITEMS;j++);
	return j;
}
unsigned find_max_strlen(char *list[])
{
	unsigned len=0;
	unsigned max=0;
	for (int j=0;(len=strlen(list[j]))>0 && j<MAX_MENU_ITEMS;j++)
		if (max<len)
			max=len;
	return max+3;
}
int panel(void)
{
	int y=1;

	MY_MENU my_menu[4]={{0}};
	//MY_MENU *current_menu = NULL;

	char *menu0_items[] = {"File","Send","Save","Save as","\0"};	//last item must have strlen of zero
	char *menu1_items[] = {"Edit","Copy","Paste","Copy all","\0"};
	char *menu2_items[] = {"Screen","Clear screen","222","333","\0"};
	char *menu3_items[] = {"Configuration","Port","Echo","Line termination","Load configuration","Save configuration","\0"};

	char **menu_items[] = {menu0_items,menu1_items,menu2_items,menu3_items};


	//BOX b = {x,y,width,height};

	initscr();	//Start curses mode
	cbreak();	//Disable buffering but unlike raw() allow control-c to send SIGINT
	noecho();	//Don't echo keys
	keypad(stdscr,TRUE);	//Enable arrow and function keys
	//
		int screen_width=0;
		int screen_height=0;
		getmaxyx(stdscr,screen_height,screen_width);

		WINDOW *main_window = newwin(screen_height-4,screen_width,4,0);
				box(main_window,0,0);
		PANEL 	*panel = new_panel(main_window);

		(void)panel;	//To avoid unused variable compiler error

	//
	int x_pos=0;
	for (int i=0;i<ARRAY_SIZE(my_menu); i++) {
		my_menu[i].menu_items = menu_items[i];
		my_menu[i].number_of_menu_items = count_items(my_menu[i].menu_items);
		my_menu[i].width = find_max_strlen(my_menu[i].menu_items);

		dbg_printf("number_of_menu_items=%u\n",my_menu[i].number_of_menu_items);

		my_menu[i].box=(BOX){x_pos,y,my_menu[i].width,my_menu[i].number_of_menu_items+2};
		x_pos += my_menu[i].width;

		print_menu_title(&my_menu[i]);
		//print_menu_all(&my_menu[i]);
	}

	curs_set(0);
	/* Update the stacking order. 2nd panel will be on top */
	update_panels();

	/* Show it on the screen */
	doupdate();

	int ch;
	int alt_pressed = 0;
	while ((ch = getch()) != ERR) {

		if (alt_pressed==1)
			alt_pressed = 2;
		switch (ch) {
			case KEY_RIGHT:
				//current_menu->select_right();
				break;
			case KEY_LEFT:
				//current_menu->select_left();
				break;
			case 27:
			case 195:	//code in xterm
				alt_pressed = 1;
				break;
			case 102:
			case 166:	//code in xterm
				if (alt_pressed == 2) {
					//wprintw(main_window,"ALT_F %d\n",ch);
					//wrefresh(main_window);
					//current_menu = &my_menu[0];
					//current_menu->select();
					print_menu_all(&my_menu[0]);

					break;
				}
				//No break - goto default
			default:
				wprintw(main_window,"a=%u key=%u\n",alt_pressed,ch);
				wrefresh(main_window);
				break;
		}
		if (alt_pressed==2)
			alt_pressed = 0;



	}
	endwin();
	return EXIT_SUCCESS;
}
int panel_working(void)
{
	int lines = 10, cols = 20, y = 2, x = 4, i;
	WINDOW *my_wins[3];
	PANEL  *my_panels[3];


	initscr();	//Start curses mode
	cbreak();	//Disable buffering but unlike raw() allow control-c to send SIGINT
	noecho();	//Don't echo keys
	keypad(stdscr,TRUE);	//Enable arrow and function keys

	my_wins[0] = (WINDOW *)my_panels;	//This is just to avoid my_panels set but not used compiler error

	/* Create windows for the panels */
	my_wins[0] = newwin(lines, cols, y, x);
	my_wins[1] = newwin(lines, cols, y, x + cols);
	my_wins[2] = newwin(lines, cols, y, x + cols*2);

	/*
	 * Create borders around the windows so that you can see the effect
	 * of panels
	 */
	for(i = 0; i < 3; ++i)
		box(my_wins[i], 0, 0);

	/* Attach a panel to each window */ 	/* Order is bottom up */
	my_panels[0] = new_panel(my_wins[0]); 	/* Push 0, order: stdscr-0 */
	my_panels[1] = new_panel(my_wins[1]); 	/* Push 1, order: stdscr-0-1 */
	my_panels[2] = new_panel(my_wins[2]); 	/* Push 2, order: stdscr-0-1-2 */


	wattron(my_wins[2],A_BOLD);
	mvwprintw(my_wins[2],5,5,"ramon");
	mvwchgat(my_wins[2],5,5,1,A_BLINK,1,NULL);
	curs_set(0);

	/* Update the stacking order. 2nd panel will be on top */
	update_panels();

	/* Show it on the screen */
	doupdate();

	while (1)
		getch();
	endwin();
	return EXIT_SUCCESS;
}


void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}
