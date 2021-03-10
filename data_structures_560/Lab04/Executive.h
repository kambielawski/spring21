#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "BinarySearchTree.h"
using namespace std;

class Executive {
private:
BinarySearchTree<int>* bst; 
BinarySearchTree<int>* profileTree;

public:
Executive(char *fileName);
~Executive();
void run();
void printMenu() const;
int getInt(string prompt, string onError) const;
void readIntoBST(ifstream& infile); 
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
float profileBuild(int size);
float profileFindMin(int size);
float profileFindMax(int size);
float profileDeleteMin(int size);
float profileDeleteMax(int size);
void preorderPrint();
void postorderPrint();
void inorderPrint();
void profile();

};

#endif
