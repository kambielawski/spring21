#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include <string>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "HashTable.h"
using namespace std;

struct StudentEntry {
  int studentId;
  string studentName;

  bool operator==(const StudentEntry& rhs) {
    return (studentId == rhs.studentId && studentName == rhs.studentName);
  }
};


class Executive {
private:
ifstream &m_infile;
HashTable<StudentEntry> m_hashtable;
void readFileIntoHashTable(ifstream& infile);
void printMenu() const;

public:
Executive(ifstream& infile);
~Executive();
void run();
void addStudent();
void removeStudent();
void printStudentsList() const;
void findStudent();
int getInt(std::istream& stream) const;
StudentEntry parseStudentEntry(string studentEntry) const;

};

#endif
