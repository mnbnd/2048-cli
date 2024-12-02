CXX=		g++
CXXFLAGS=	-g -Wall -std=gnu++11
SHELL=		bash

all:		2048

2048:		main.cpp Board.h Node.h
	$(CXX) $(CXXFLAGS) -o $@ main.cpp

clean:
	rm -f 2048

