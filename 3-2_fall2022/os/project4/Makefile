CC = gcc

replacementPage_exe : main.o input.o replacement.o page.o
	gcc -o replacementPage_exe main.o input.o replacement.o page.o

main.o : main.c
	gcc -c main.c

input.o : input.c
	gcc -c input.c

replacement.o : replacement.c
	gcc -c replacement.c

page.o : page.c
	gcc -c page.c

clean :
	rm *.o replacementPage_exe