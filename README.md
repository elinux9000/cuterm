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
MY_MENU: 
A menu has an associated curses window and panel.  The window defines the size of the panel.
A box contains the size.  A menu has a title, state, parent, and children.
The children is an array of menus.

Drawing:


Design
Implementation
Test

