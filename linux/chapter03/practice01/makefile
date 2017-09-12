main:	main.o copy.o capitalize.o
	gcc -o main main.o copy.o capitalize.o
main.o:	main.c copy.h capitalize.h
	gcc -c main.c
copy.o:	copy.c copy.h
	gcc -c copy.c
capitalize.o:	capitalize.c capitalize.h
	gcc -c capitalize.c
