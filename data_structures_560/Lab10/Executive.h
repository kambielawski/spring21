#include <iostream>
#include <fstream>
#include <string>

#include "Graph.h"
using namespace std;

#ifndef EXECUTIVE_H
#define EXECUTIVE_H

class Executive
{
private:
Graph *graph;
int** inp_arr;
int graph_size;

/* Helper functions */
void printMenu() const;
void readIntoArray(ifstream& infile);
int getChoice(string prompt) const;

/* Menu options */
void buildGraph();
void breadthFirstSearch();
void depthFirstSearch();
void kruskal();
void prim();

public:
Executive(char *filename);
~Executive();
void run();

};

#endif
