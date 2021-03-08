#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include <iostream>
#include <fstream>
#include "BinarySearchTree.h"
using namespace std;

class Executive {
private:
BinarySearchTree<int>* bst; 

public:
Executive(char *fileName);
~Executive();
void run();
void printMenu() const;
int getInt(string prompt, string onError) const;
void addItem();
void deleteItem();
void findMin();
void findMax();
void deleteMin();
void deleteMax();
void inorderSuccessor();
void levelOrder();
void spiralLevelOrder();
void leftSideView();
void rightSideView();
void experimentalProfiling();

};

#endif
