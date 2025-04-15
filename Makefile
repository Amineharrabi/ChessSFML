# Compiler and flags
CXX = g++
CXXFLAGS = -Isrc/include -Wall
LDFLAGS = -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lopengl32

SRC = $(wildcard coding/*.cpp)

all: main

main:
	$(CXX) -o main $(SRC) $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f main
	rm -f *.o
	rm -f src/*.o