main: main.o Executive.o
	g++ Executive.o main.o -o main

%.o: %.cpp BinarySearchTree.h BinarySearchTree.cpp
	g++ -c $<

clean:
	rm -f main *.o
