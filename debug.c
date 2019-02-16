#include "debug.h"

WINDOW *Debug_win;
int Debug_line;
int Debug_height=10;
int Debug_width;
int Debug_line;
int Debug_y_pos;
PANEL *Debug_panel;
bool Debug=true;

void debug_printf(bool debug_output, const char *fmt, ...)
{
	va_list argptr;
	va_start(argptr, fmt);

	if (debug_output && Debug) {
		getmaxyx(Debug_win,Debug_height,Debug_width);
		mvwprintw(Debug_win,Debug_line,0,fmt, argptr);
		Debug_line++;
		Debug_line %= Debug_height;
		wrefresh(Debug_win);
	}
	va_end(argptr);
}
void debug_init(WINDOW *main_win)
{
	int main_height;
	
	if (Debug) {
		getmaxyx(main_win,main_height,Debug_width);
		Debug_win = newwin(Debug_height, Debug_width,main_height,0);
		Debug_panel = new_panel(Debug_win);
		box(Debug_win,0,0);
	}
}
