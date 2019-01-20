#comment
.PHONY: clean

cuterm:	main.c 
	gcc -o cuterm main.c -lncurses -lmenu

clean:
	rm -f *.o cuterm