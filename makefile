# Makefile to LBP IMAGE COMPARATION

OBJS	= src/lbp.o src/main.o src/auxiliar.o
SOURCE	= src/lbp.c src/main.c src/auxiliar.c
HEADER	= src/lbl.h src/auxiliar.h
OUT	= LBP
CC	 = gcc
FLAGS	 = -g -c -Wall -Wextra -Werror
LFLAGS	 = -lm

all: lbp

lbp: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS) 

valgrind: lbp
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes ./LBP

clean:
	rm -f *.o *.gch $(OUT)
