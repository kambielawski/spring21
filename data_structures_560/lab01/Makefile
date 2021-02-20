Lab01: main.o Executive.o
	g++ -g -std=c++11 main.o Executive.o -o Lab01
main.o: main.cpp
	g++ -c main.cpp
Executive.o: Executive.h Executive.cpp DoublyLinkedList.h DoublyLinkedList.cpp
	g++ -c Executive.cpp
clean:
	rm Lab01 *.o
