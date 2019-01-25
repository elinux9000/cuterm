/*
 * my_menu.h
 *
 *  Created on: Jan 23, 2019
 *      Author: rc
 */

#ifndef MY_MENU_H_
#define MY_MENU_H_
#include <stdlib.h>
#include <ncurses.h>			/* ncurses.h includes stdio.h */
#include <string.h>
#include <menu.h>
#include <panel.h>
#define MAX_MENU_ITEMS	20
#define	DEBUG_PRINT false
#define dbg_printf( ... ) do { if (DEBUG_PRINT) { printf(__VA_ARGS__);printw(__VA_ARGS__);} }while(0)
struct box_tag
{
	int x;
	int y;
	int width;
	int height;
};
typedef struct box_tag BOX;
struct menu_tag
{
	WINDOW *win;
	PANEL  *panel;
	BOX	box;
	char 	**menu_items;
	unsigned number_of_menu_items;
	unsigned width;
};
typedef struct menu_tag MY_MENU;


#endif /* MY_MENU_H_ */
