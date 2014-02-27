CXX=g++ -std=c++11 -I/usr/include -Wall -pedantic
LDFLAGS=-lGL -lGLU -lglut -lGLEW
SRC=*.cpp
OBJ=*.o
PROJECT='Introduction to Computer Graphics'
PROD=GFX

build:
	clear
	$(CXX) $(SRC) $(LDFLAGS) -o $(PROD)

run:
	./$(PROD)

class:
	./.cpp_class.sh $(NAME) $(PROJECT)

clean:
	rm -rf *.{o}

.PHONY: clean class run
