#comment
.PHONY: clean

cuterm:	main.c screen.c
	#rm cuterm
	gcc -std=c99 -Wall -Werror -o cuterm main.c screen.c -lncurses -lmenu -lpanel

clean:
	rm -f *.o cuterm