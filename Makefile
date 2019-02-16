#comment
.PHONY: clean

cuterm:	main.c screen.c application.c debug.c
	#rm cuterm
	#gcc -std=c99 -Wall -Werror -Wno-unused-variable -Wunused-but-set-variable -o cuterm application.c main.c screen.c -lncurses -lmenu -lpanel
	gcc -std=c99 -g3 -Wall -Wno-unused-variable -Wunused-but-set-variable -o cuterm *.c -lncurses -lmenu -lpanel

clean:
	rm -f *.o cuterm
