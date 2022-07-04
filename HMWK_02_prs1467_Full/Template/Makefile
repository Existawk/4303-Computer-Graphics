# Dalio, Brian A.
# dalioba
# 2021-04-24

PROJS   = transformsTest render
CC      = gcc
CFLAGS  = -g -Wall -Wextra -fsanitize=address -fsanitize=leak -static-libasan
LIBS    = -lm

all : $(PROJS)

transformsTest: matrix.h matrix.c transforms.h transforms.c transformsTest.c
	$(CC) $(CFLAGS) -o transformsTest matrix.c transforms.c transformsTest.c $(LIBS)

render: matrix.h matrix.c model.h model.c parameters.h parameters.c render.c transforms.h transforms.c
	$(CC) $(CFLAGS) -o render matrix.c model.c parameters.c render.c transforms.c $(LIBS)

clean:
	rm -f *.o $(PROJS)
