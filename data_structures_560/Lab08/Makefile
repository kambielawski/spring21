main: main.o Executive.o
	g++ main.o Executive.o -o main
%.o: %.cpp LeftistHeap.h LeftistHeap.cpp
	g++ -c $<
clean:
	rm -f *.o main
