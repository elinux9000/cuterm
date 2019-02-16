cuterm is a curses application designed to communicate with RS232 devices.

Menu navigation:
ALT-x opens/closes the menu beginning with x.  When the menu is opened the first item is selected.  Subsequent items are selected with the arrow keys




API - toggle, open, close menu
API - select next


Iteration 1
Requirements
Basic menu functionality.  Display File, Edit, Settings.  
Demonstrate menu item selection and callback.  Demonstrate hierarchical menues

Analysis
Data structures:
my_menut_t: 
A menu has the following properties:
curses window 
curses panel
The window defines the size of the panel.
box contains the size
title
state (open or closed)
parent
children:an array of menus.
draw_open: function to call when selected , will depend on selected
draw_closedll : function to call when deselected

Will need the left and right menus 
Select with enter key, or alt-letter
Navigation with arrows

Main loop
	based on key will select current_menu right left down up

When selected the menu will draw itself
	This means resizing the window
When unselected menu will redraw


Drawing:
updatepanels()
doupdate()


Design





Implementation
Test

