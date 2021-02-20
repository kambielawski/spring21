#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <climits>
#include <exception>

#include "LinkedList.h"
using namespace std;

class Executive {
private:
ifstream m_infile;
LinkedList<int> m_list;
void displayMenu() const;
void readFileIntoList();
int getInt(std::istream& stream) const;
void insertIntoList();
void deleteFromList();
void printItemAtIndex() const;
void findItemInList() const;
void findNextItem() const;
void deleteDuplicates();

public:
Executive(char *fileName);
~Executive();

void run();
};

Executive::Executive (char *fileName) {
  m_infile.open(fileName);
  if (m_infile.is_open()) {
    this->readFileIntoList();
  } else {
    throw runtime_error("couldn't open file");
  }
}

Executive::~Executive() {}

void Executive::run() {
  int choice;

  while (choice != 11) {
    this->displayMenu();
    choice = this->getInt(cin);

    cout << "\n----------------\n";
    switch (choice) {
      case 1: cout << "Is Empty: " << m_list.isEmpty();
        break;
      case 2: cout << "Length: " << m_list.length(); 
        break;
      case 3: this->insertIntoList();
        break;
      case 4: this->deleteFromList(); // delete
        break;
      case 5: this->deleteDuplicates();
        break;
      case 6: this->findItemInList(); 
        break;
      case 7: this->findNextItem();
        break;
      case 8: 
        cout << "List: ";
        m_list.printList();
        break;
      case 9: 
        cout << "Reversed list:";
        m_list.printListReverse();
        break;
      case 10: this->printItemAtIndex();
        break;
      case 11: cout << "Exiting...";
        break;
      default: cout << "Invalid input. Enter a number between 1-11";
        break;
    }
    cout << "\n----------------\n";
  }
}

/* 
Gets an integer from an istream object
*/
int Executive::getInt(std::istream& stream) const {
  string input;
  int value;
  bool loop = true;

  while (loop) {
    std::getline(stream, input);
    std::stringstream linestream(input);

    if (!(linestream >> value)) {
      cout << "Invalid input. Enter an integer.\n";
      continue; // input was not an integer
    } else {
      loop = false;
    }
  }
  return value;
}

void Executive::insertIntoList() {
  string input;
  int newItem;

  cout << "Choose a number to be inserted: ";
  newItem = this->getInt(cin);
  m_list.insertFront(newItem);
}

void Executive::findNextItem() const {
  int item;
  cout << "Enter the number to find its next element: ";
  item = this->getInt(cin);

  if (m_list.find(item)) {
    int index = m_list.getIndexOfItem(item);
    if (index < m_list.length() - 1) {
      cout << m_list.getItemAtIndex(index + 1) << " is next after " << item;
    } else {
      cout << "None";
    }
  } else {
    cout << "Could not find element " << item << " in list";
  }
}

void Executive::deleteFromList() {
  int itemToBeDeleted;

  cout << "Choose a number to be deleted from the list: ";
  itemToBeDeleted = this->getInt(cin);

  if (m_list.find(itemToBeDeleted)) {
    m_list.removeItem(itemToBeDeleted);
    cout << itemToBeDeleted << " has been deleted.";
  }
  else {
    cout << itemToBeDeleted << " is not in the list. Deleted nothing.";
  }
}

void Executive::deleteDuplicates() {
  int index = 0;
  int item;

  while (index < m_list.length()) {
    item = m_list.getItemAtIndex(index);  
    while (m_list.countItem(item) > 1) {
      m_list.removeItem(item); 
    }
    index++;
  }

  cout << "Duplicates deleted.";
}

void Executive::printItemAtIndex() const {
  int index;
  bool validIndex = false;

  while (!validIndex) {
    cout << "Enter index of item: ";
    index = this->getInt(cin);
    if (index < 0 || index > m_list.length() - 1) {
      cout << "Index out of list range.\n";
    } else {
      validIndex = true;
      cout << "Item at index " << index << " is " << m_list.getItemAtIndex(index);
    }
  }
}

void Executive::findItemInList() const {
  int itemToFind;
  cout << "Enter an item to find: ";
  itemToFind = this->getInt(cin);
  if (m_list.find(itemToFind)) {
    cout << itemToFind << " is in the list";
  } else {
    cout << itemToFind << " is not in the list";
  }
}

void Executive::readFileIntoList() {
  string line;
  int num;
  while (m_infile >> line) {
    try {
      num = stoi(line);
      m_list.insertFront(num);
    } catch (exception& e) {
      cout << "Error reading file: ";
      throw std::runtime_error(e.what());
    }
  }
}

void Executive::displayMenu() const {
  cout << "Choose one operation from the options below:\n\n"
  << "1. Is Empty\n"
  << "2. Length\n"
  << "3. Insert\n"
  << "4. Delete\n"
  << "5. Delete Duplicates\n"
  << "6. Find\n"
  << "7. Find Next\n"
  << "8. Print\n"
  << "9. Reverse List\n"
  << "10. Print At\n"
  << "11. Exit\n\n"
  << "Input: ";
}

#endif
