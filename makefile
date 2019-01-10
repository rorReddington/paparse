OUTFILE=programm
 
COMPILE_FLAGS=-c -w -std=c99 -O3
LINK_FLAGS=-O3

all:
	gcc $(COMPILE_FLAGS) *.c		
	gcc $(LINK_FLAGS) -o $(OUTFILE) *.o
	rm *.o
	strip -s $(OUTFILE)