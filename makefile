my_set: my_set.o set.o set.h
	gcc -Wall -ansi -pedantic set.o my_set.o  -o my_set
my_set.o: my_set.c set.h
	gcc -c -Wall -ansi -pedantic my_set.c -o my_set.o
set.o: set.c set.h
	gcc -c -Wall -ansi -pedantic set.c -o set.o