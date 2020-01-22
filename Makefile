CC = gcc
CXX = g++
AR = ar
LD = g++

CFLAGS =  -Wall -Werror -fpic -O2
LDFLAGS =  -s

OUT = stagekit
OBJ = main.o stagekit.o

SOUT = libstagekit.so
SOBJ = extern.o stagekit-s.o

all: release shared

release: $(OBJ)
	$(LD) -o $(OUT) $(OBJ) $(LDFLAGS)

shared: $(SOBJ)
	$(LD) -shared -o $(SOUT) $(SOBJ) $(LDFLAGS)

extern.o: extern.c
	$(CC) $(CFLAGS) -c extern.c -o extern.o -DSHARED_LIB

stagekit-s.o: stagekit.c
	$(CC) $(CFLAGS) -c stagekit.c -o stagekit-s.o -DSHARED_LIB

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

stagekit.o: stagekit.c
	$(CC) $(CFLAGS) -c stagekit.c -o stagekit.o

clean:
	rm $(OBJ) $(OUT) $(SOBJ) $(SOUT)
