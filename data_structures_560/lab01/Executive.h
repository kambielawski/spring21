#include <iostream>
#include <exception>
#include <string>
#include <fstream>
#include <sstream>

#include "DoublyLinkedList.h"

#ifndef EXECUTIVE_H
#define EXECUTIVE_H

class Executive
{
private:
std::ifstream m_infile;
DoublyLinkedList<int> list;

public:
Executive(char *fileName);
~Executive();
void run();
void printMenu() const;
void readFileIntoList();
int getValidChoice() const;
int getValidNum(std::string prompt, std::string onError) const;
void getIsEmpty();
void getLength();
void insertItem();
void deleteItem();
void find();
void findPrev();
void appendList();
void forwardTraverse();
void backwardTraverse();
void trimWhitespace(std::string* str);

};

#endif

