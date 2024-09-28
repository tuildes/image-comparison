OBJS	= lbp.o
SOURCE	= lbp.c
# HEADER	= library.h
OUT	= LBP
CC	 = gcc
FLAGS	 = -g -c -Wall -Wextra -Werror
LFLAGS	 = -lm

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

lbp.o: lbp.c
	$(CC) $(FLAGS) lbp.c 

clean:
	rm -f *.o *.gch $(OUT)
