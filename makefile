OBJS	= tile-renderer.o
SOURCE	= tile-renderer.c
HEADER	= 
OUT	= dugeon2d
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = -lglut -lGL -lGLU -lm -ldl -ffast-math

makefile: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

tile-renderer.o: tile-renderer.c
	$(CC) $(FLAGS) tile-renderer.c 

clean:
	rm -f $(OBJS) $(OUT)
