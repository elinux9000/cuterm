/*
 * application.h
 *
 *  Created on: Jan 25, 2019
 *      Author: rc
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_
#include "my_menu.h"
//#define SELF_PTR	(struct app_tag *self)
struct app_tag
{
	MY_MENU	**current_menu;
	void(*constructor)(struct app_tag *self);
	int (*add_menu)(struct app_tag *self,MENU_LIST *menu);

};
typedef struct app_tag MY_APP;

int add_menu(MY_APP* app,MENU_LIST *menu);

#endif /* APPLICATION_H_ */
