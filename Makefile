program: mainZnaki.o znaki.o
	gcc mainZnaki.o znaki.o -o program

mainZnaki.o: mainZnaki.c znaki.h
	gcc -c mainZnaki.c

znaki.o: znaki.c znaki.h
	gcc -c znaki.c