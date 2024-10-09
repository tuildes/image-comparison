# Makefile to LBP IMAGE COMPARATION

OBJS	= src/lbp.o src/main.o src/auxiliar.o
SOURCE	= src/lbp.c src/main.c src/auxiliar.c
HEADER	= src/lbp.h src/auxiliar.h
OUT	= LBP
CC	 = gcc
FLAGS	 = -g -c -Wall -Wextra -Werror
LFLAGS	 = -lm

all: LBP

LBP: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

src/lbp.o: src/lbp.c
	$(CC) $(FLAGS) src/lbp.c -o src/lbp.o

src/main.o: src/main.c
	$(CC) $(FLAGS) src/main.c -o src/main.o

src/auxiliar.o: src/auxiliar.c
	$(CC) $(FLAGS) src/auxiliar.c -o src/auxiliar.o

clean:
	rm -f $(OBJS) $(OUT)

valgrind: LBP
	valgrind ./LBP

valgrind_leakcheck: ./LBP
	valgrind --leak-check=full ./LBP

valgrind_extreme: LBP
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes ./LBP
