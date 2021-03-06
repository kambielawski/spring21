#include <iostream>
#include <fstream>
#include <sstream>
#include "MinMaxHeap.h"
using namespace std;

#ifndef EXECUTIVE_H
#define EXECUTIVE_H

class Executive
{
private:
MinMaxHeap<int>* heap;
char *file;

void readIntoHeap(ifstream& infile);
void readIntoArray(ifstream& infile);
void printMenu() const;
int getChoice(string prompt) const;

/* Menu options */
void buildHeap();
void insertItem();
void deleteMin();
void printMinLevels() const;
void printMaxLevels() const;

public:
Executive(char *filename);
~Executive();
void run();

};

#endif
