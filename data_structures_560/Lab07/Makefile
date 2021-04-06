main: main.o Executive.o
	g++ main.o Executive.o -o main
%.o: %.cpp MinMaxHeap.h MinMaxHeap.cpp
	g++ -c $<
clean:
	rm -f *.o main
