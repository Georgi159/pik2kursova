FLAGS=-std=c11 -Wall -pedantic -Wextra -fstack-protector-all

main.out : main.o  sort.o print.o
	gcc $(FLAGS) main.o  sort.o print.o  -g3 -o main.out

sort.o : sort.c main.h
	gcc $(FLAGS) -c sort.c -g3 -o sort.o -O3

main.o : main.c  main.h
	gcc $(FLAGS) -c main.c -g3 -o main.o

print.o : print.c  main.h
	gcc $(FLAGS) -c print.c -g3 -o print.o

valm :  main.out 
	colour-valgrind --leak-check=yes --track-origins=yes  ./main.out

.PHONY: all clean valm

all : main.out 

clean : 
	rm -v main.out  main.o  sort.o print.o