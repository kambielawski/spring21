#include <iostream>

#include "DisjointSets.h"
#include "K_Ary_Heap.h"
using namespace std;

#ifndef GRAPH_H
#define GRAPH_H

class Graph
{
private:
int** adjacency_matrix;
int graph_size;

public:
Graph();
~Graph();
void buildGraph(int** array, int size);
int*** breadthFirstSearch();
int*** depthFirstSearch();
int** kruskal();
int** prim();

};

#endif
