CC = gcc
CXX = g++
AR = ar
LD = g++

CFLAGS = -Wall -Werror -O2
LDFLAGS = -s

all: stagekit libstagekit.so libstagekit.a

stagekit: main.o libstagekit.a
	$(LD) -o stagekit main.o libstagekit.a $(LDFLAGS)

libstagekit.so: stagekit-s.o
	$(LD) -shared -o libstagekit.so stagekit-s.o $(LDFLAGS)

libstagekit.a: stagekit.o
	$(AR) -crs libstagekit.a stagekit.o

stagekit-s.o: stagekit.cpp
	$(CXX) $(CFLAGS) -fpic -c stagekit.cpp -o stagekit-s.o

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp -o main.o

stagekit.o: stagekit.cpp
	$(CXX) $(CFLAGS) -c stagekit.cpp -o stagekit.o

clean:
	rm stagekit libstagekit.so libstagekit.a *.o	
