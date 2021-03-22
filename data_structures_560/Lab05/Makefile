main: main.o Executive.o
	g++ main.o Executive.o -o main
%.o: %.cpp K_Ary_Heap.h K_Ary_Heap.cpp HeapInterface.h
	g++ -c $<
clean:
	rm -f *.o main
