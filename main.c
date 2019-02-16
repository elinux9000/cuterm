#include <ncurses.h>
#include <string.h>
#include <signal.h>
int panel_1(void);
int keys(void);
void do_resize(int dummy)
{
	border(0,0,0,0,0,0,0,0);
}
int barmenu(const char **array, const int row, const int col, const int arraylength, const int width, int menulength, int selection);
int main(void)
{
	int selection,row=1, col=10, arraylength=10, width=5, menulength=5;
	const char *testarray[]= {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
	//WINDOW win;

	//return keys();
	return panel_1();



	signal(SIGWINCH, do_resize);
	initscr();
	noecho();
	keypad(stdscr,TRUE);
	border(0,0,0,0,0,0,0,0);//chtype ls, chtype rs, chtype ts, chtype bs, chtype tl, chtype tr, chtype bl, chtype br);

	//box(win,0,0);

	selection=barmenu(testarray,row,col,arraylength,width,menulength,3);

	mvprintw(15,0,"Selection= %d",selection);
	refresh();
	getch();

	endwin();
	return 0;
}

int barmenu(const char **array,const int row, int column, const int arraylength, const int width, int menulength, int selection)
{
	int counter;
	int offset=0;
	int ky=0;
	int col;
	char formatstring[7];
	curs_set(0);

	if (arraylength < menulength)
		menulength=arraylength;

	if (selection > menulength)
		offset=selection-menulength+1;

	sprintf(formatstring,"%%-%ds",width); // remove - sign to right-justify the menu items

	while(ky != 27) {
		col = column;
		for (counter=0; counter < menulength; counter++) {
			if (counter+offset==selection)
				attron(A_REVERSE);
			mvprintw(row,col,formatstring,array[counter+offset]);
			//printf("123\n");
			col +=strlen(array[counter+offset])+1;
			attroff(A_REVERSE);
		}

		ky=getch();

		switch(ky) {
		case KEY_LEFT:
			if (selection) {
				selection--;
				if (selection < offset)
					offset--;
			}
			break;
		case KEY_RIGHT:
			if (selection < arraylength-1) {
				selection++;
				if (selection > offset+menulength-1)
					offset++;
			}
			break;
		case KEY_HOME:
			selection=0;
			offset=0;
			break;
		case KEY_END:
			selection=arraylength-1;
			offset=arraylength-menulength;
			break;
		case KEY_PPAGE:
			selection-=menulength;
			if (selection < 0)
				selection=0;
			offset-=menulength;
			if (offset < 0)
				offset=0;
			break;
		case KEY_NPAGE:
			selection+=menulength;
			if (selection > arraylength-1)
				selection=arraylength-1;
			offset+=menulength;
			if (offset > arraylength-menulength)
				offset=arraylength-menulength;
			break;
		case 10: //enter
			return selection;
			break;
		case KEY_F(1): // function key 1
			return -1;
		case 27: //esc
			// esc twice to get out, otherwise eat the chars that don't work
			//from home or end on the keypad
			ky=getch();
			if (ky == 27) {
				curs_set(0);
				mvaddstr(9,77,"   ");
				return -1;
			} else if (ky=='[') {
				getch();
				getch();
			} else
				ungetch(ky);
		}
	}
	return -1;
}
int keys(void)
{
    int lastch = ERR;
    int ch;
    WINDOW *win;

    initscr();
    (void) cbreak();		/* take input chars one at a time, no wait for \n */
    (void) noecho();		/* don't echo input */

    printw("Typing any function key will disable it, but typing it twice in\n");
    printw("a row will turn it back on (just for a demo).");
    refresh();

    win = newwin(LINES - 2, COLS, 2, 0);
    scrollok(win, TRUE);
    keypad(win, TRUE);
    wmove(win, 0, 0);

    while ((ch = getch()) != ERR) {
	const char *name = keyname(ch);
	wprintw(win, "Keycode %d, name %s\n",ch,name != 0 ? name : "<null>");
	wclrtoeol(win);
	wrefresh(win);
	if (ch >= KEY_MIN) {
	    keyok(ch, FALSE);
	    lastch = ch;
	}
	else if (lastch >= KEY_MIN) {
	    keyok(lastch, TRUE);
	}
    }
    endwin();
    return 0;
}
