#include <iostream>
#include <fstream>

#include "DisjointSets.h"
using namespace std;

#ifndef EXECUTIVE_H
#define EXECUTIVE_H

class Executive
{
private:
DisjointSets<int> *ds;
int num_items;
int *num_array;

void printMenu() const;
int getChoice(string prompt) const;
int* readIntoArray(ifstream& infile);

/* Menu functions */
void makeSet();
void unionByRank();
void find();
void pathCompression();
void printPath();

public:
Executive(char *filename);
~Executive();
void run();

};

#endif
