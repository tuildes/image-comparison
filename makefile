# Makefile to LBP IMAGE COMPARATION

OBJS	= lbp.o
SOURCE	= lbp.c
# HEADER	= library.h
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
