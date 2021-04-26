main: main.o Executive.o
	g++ main.o Executive.o -o main
%.o: %.cpp DisjointSets.h DisjointSets.cpp
	g++ -c $<
clean:
	rm -f *.o main
