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
struct box_tag
{
	int x;
	int y;
	int width;
	int height;
};
typedef struct box_tag BOX;
enum state_tag
{
	UNDISPLAYED=0,DISPLAYED
};
typedef enum state_tag MENU_STATE;



typedef struct my_menu_tag {
	WINDOW *win;
	PANEL *panel;
	BOX 	box;
	struct my_menu_tag *parent;
	struct my_menu_tag **items;
	char *title;

} my_menu_t;











struct menu_tag
{
	WINDOW *win;
	PANEL  *panel;
	BOX	box;
	struct menu_tag *parent;
	struct menu_tag **items;
	char	*title;
	void(*action)(struct menu_tag *self);
	char 	**menu_items;
	unsigned number_of_menu_items;
	unsigned width;
	MENU_STATE state;
	signed selected;
	void (*select_right)(struct menu_tag *self);
	void (*select_left)(struct menu_tag *self);
	void (*select)(struct menu_tag *self);
	void (*constructor)(struct menu_tag *self);
};
typedef struct menu_tag MY_MENU;
struct menu_list
{
	char	*title;
	int (*func)(MY_MENU *self);
};
typedef struct menu_list MENU_LIST;


#endif /* MY_MENU_H_ */
