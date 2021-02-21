#include <string>
#include <stdexcept>
#include <fstream>
#include <iostream>

#include "HashTable.h"

#ifndef EXECUTIVE_H
#define EXECUTIVE_H

class Executive
{
private:
HashTable<int>* quadraticProbingTable;
HashTable<int>* doubleHashingTable;

public:
Executive(char *file);
~Executive();
void run();
void readFileIntoTables(std::ifstream& infile);
void printMenu() const;
void insertItem();
void deleteItem();
void findItem();
void printTables();

};

#endif
