#comment
.PHONY: clean

cuterm:	main.c screen.c
	gcc -o cuterm main.c screen.c -lncurses -lmenu -lpanel

clean:
	rm -f *.o cuterm