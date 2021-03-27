#include <iostream>
#include <fstream>
#include "MinMaxHeap.h"
using namespace std;

#ifndef EXECUTIVE_H
#define EXECUTIVE_H

class Executive
{
private:
MinMaxHeap<int>* heap;

void readIntoHeap(ifstream& infile);
void printMenu() const;
int getChoice() const;

/* Menu options */
void buildHeap();
void insertItem();
void deleteItem();
void printMinLevels() const;
void printMaxLevels() const;

public:
Executive(char *filename);
~Executive();
void run();

};

#endif
