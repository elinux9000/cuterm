#ifndef __DEBUG_H__
#define __DEBUG_H__
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <menu.h>
#include <panel.h>
#include <stdarg.h>

extern WINDOW *Debug_win;
extern int Debug_line;
extern int Debug_height;
extern int Debug_width;
extern int Debug_line;
extern int Debug_y_pos;
extern bool Debug;

void debug_init(WINDOW *main_win);
void debug_printf(bool, const char *fmt,...);
#define dbg_printf(...) debug_printf(debug_output,__VA_ARGS__)
#endif

