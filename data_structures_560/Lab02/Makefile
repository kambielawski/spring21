
main: Executive.o main.o
	g++ Executive.o main.o -o main

%.o: %.cpp  HashTable.h HashTableInterface.h LinkedList.h
	g++ -c $<

clean:
	rm -f main
	rm -f *.o

