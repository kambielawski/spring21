main: main.o Executive.o Graph.o
	g++ main.o Executive.o Graph.o -o main
%.o: %.cpp DisjointSets.h DisjointSets.cpp K_Ary_Heap.h K_Ary_Heap.cpp HeapInterface.h
	g++ -c $<
clean:
	rm -f *.o main
