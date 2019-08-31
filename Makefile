CC = gcc
CXX = g++
AR = ar
LD = g++

INC = 
CFLAGS =  -Wall -O2
RESINC = 
LIBDIR = 
LIB = 
LDFLAGS =  -s

OUT = stagekit

OBJ = main.o stagekit.o

all: release

release: $(OBJ)
	$(LD) $(LIBDIR) -o $(OUT) $(OBJ) $(LDFLAGS) $(LIB)

main.o: main.c
	$(CC) $(CFLAGS) $(INC) -c main.c -o main.o

stagekit.o: stagekit.c
	$(CC) $(CFLAGS) $(INC) -c stagekit.c -o stagekit.o

clean: 
	rm $(OBJ) $(OUT)
