#include <iostream>
#include <fstream>
#include <string>

#include "LeftistHeap.h"
using namespace std;

#ifndef EXECUTIVE_H
#define EXECUTIVE_H

class Executive
{
private:
LeftistHeap<int> *heap;
string file_name;

int getChoice(string prompt) const;
void printMenu() const;
void readIntoHeap(ifstream& infile, LeftistHeap<int> *heap); 

/* Menu options */
void buildHeap();
void insertItem();
void concatenate();
void deleteMin();
void findMin();
void inorderTraversal() const;
void levelOrderTraversal() const;

void test();

public:
Executive(char *filename);
~Executive();
void run();


};

#endif
