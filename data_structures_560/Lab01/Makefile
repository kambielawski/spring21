main: main.o
	g++ -g -std=c++11 -Wall main.o -o main 

main.o: main.cpp Executive.h LinkedList.h
	g++ -c main.cpp

clean:
	rm -f main *.o
