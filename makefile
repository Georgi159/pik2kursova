
CC=-std=c11 -Wall -pedantic -Wextra -fstack-protector-all
#-lrt 

main.out : main.o  sort.o 
	gcc $(CC) main.o  sort.o  -g -o main.out

sort.o : sort.c main.h
	gcc $(CC) -c sort.c -g -o sort.o -O3

main.o : main.c  main.h
	gcc $(CC) -c main.c -g -o main.o


valm :  main.out 
	colour-valgrind --leak-check=yes --track-origins=yes  ./main.out



.PHONY: all clean valm

all : main.out 


clean : 
	rm -v main.out  main.o  sort.o






# CC=-lrt -std=c11 -Wall -pedantic -Wextra  #-fstack-protector-all


# main.out : main.c  main.h
# 	gcc $(CC) main.c -g -o main.out


# all : main.out 


# clean : main.out
# 	rm -v main.out