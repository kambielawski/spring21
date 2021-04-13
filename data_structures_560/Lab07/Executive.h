#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <random>
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
void clearHeap();
void buildRandomHeap(int num_items);

/* Menu options */
void buildHeapFromFile();
void insertItem();
void findMin();
void findMax();
void deleteMin();
void deleteMax();
void printMinLevels() const;
void printMaxLevels() const;
void experimentalProfiling();

/* Timing functions */
float timeBuildHeap(int num_items);
float timeDeleteMin(int num_items);
float timeDeleteMax(int num_items);
float timeFindMin(int num_items);
float timeFindMax(int num_items);

public:
Executive(char *filename);
~Executive();
void run();

};

#endif
