lab03: main.o Executive.o
	g++ Executive.o main.o -o main

%.o: %.cpp HashTableInterface.h HashTable.h
	g++ -c $<

clean:
	rm -f main *.o
