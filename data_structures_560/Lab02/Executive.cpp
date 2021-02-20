#include "Executive.h"


int asciiSum(string str)
{
    int sum = 0;
    for (int i = 0; i < str.length(); i++)
        sum += (int) str.at(i);
    return sum;
}

inline ostream& operator << (ostream& o, const StudentEntry& rhs) {
  return o << rhs.studentId << " " << rhs.studentName;
}

Executive::Executive(ifstream& infile) : m_infile(infile) {
  this->readFileIntoHashTable(m_infile);
}

Executive::~Executive() {}

void Executive::run() {
  int choice = -1;
  while (choice != 5) {
    this->printMenu();
    choice = this->getInt(cin);
  
    switch(choice) {
      case 1: 
        this->addStudent();
        break;
      case 2:
        this->removeStudent();
        break;
      case 3:
        this->printStudentsList();
        break;
      case 4:
        this->findStudent();
        break;
      case 5:
        cout << "Exiting...\n";
        break;
      default:
        cout << "Please enter a number between 1-5\n";
        break;
    }
    cout << "--------------------\n";
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

StudentEntry Executive::parseStudentEntry(string studentEntry) const {
  StudentEntry newStudent; 
  // remove whitespace
  studentEntry.erase(remove(studentEntry.begin(), studentEntry.end(), ' '), studentEntry.end());
  studentEntry.erase(remove(studentEntry.begin(), studentEntry.end(), '\n'), studentEntry.end());
  // split string on index of colon
  int indexOfColon = studentEntry.find(':');

  if (indexOfColon != -1) {
    string studentIdStr = studentEntry.substr(0, indexOfColon);
    string studentName = studentEntry.substr(indexOfColon+1);
    int studentId;
    // convert studentIdStr to (int) studentId
    try {
      studentId = stoi(studentIdStr);
    } catch (exception& e) {
      throw std::runtime_error("Could not parse number of goals to an integer"); 
    }

    newStudent.studentName = studentName;
    newStudent.studentId = studentId;
  } else {
    throw std::runtime_error("Entry could not be parsed. Format: <Student ID>: <Student Name>");
  }
  
  return newStudent;
}

void Executive::readFileIntoHashTable(ifstream& infile) {
  string studentEntryString;
  while (!infile.eof()) {
    getline(infile, studentEntryString, ',');
    StudentEntry studentEntry = parseStudentEntry(studentEntryString);
    m_hashtable.add(asciiSum(studentEntry.studentName), studentEntry);
  }
}

void Executive::printMenu() const {
  cout << "Please choose one of the following commands:\n"
  << "1- AddStudent\n"
  << "2- RemoveStudent\n"
  << "3- PrintStudentsList\n"
  << "4- FindStudent\n"
  << "5- Exit\n\n"
  << "Input: ";
}


void Executive::addStudent() {
  StudentEntry student;
  string studentEntryString;
  cout << "Enter the record to be inserted: ";
  getline(cin, studentEntryString);
  try {
    student = this->parseStudentEntry(studentEntryString);
  } catch (exception& e) {
    cout << "Failed to successfully insert record:\n" << e.what() << endl;
  }
  if (m_hashtable.add(asciiSum(student.studentName), student)) {
    cout << "Record successfully inserted\n";
  }
}

void Executive::printStudentsList() const { 
  m_hashtable.printLists();
}

void Executive::removeStudent() {
  StudentEntry student;
  string studentEntryString;
  cout << "Enter the record to be removed: ";
  getline(cin, studentEntryString);
  try {
    student = this->parseStudentEntry(studentEntryString);
  } catch (exception& e) {
    cout << "Failed to successfully remove record:\n" << e.what() << endl;
  }
  if (m_hashtable.remove(asciiSum(student.studentName), student)) {
    cout << "Record successfully removed\n";
  } else {
    cout << "Could not find record '" << studentEntryString << "'\n";
  }
}

bool compName (StudentEntry student, int hashedStudentName)
{
    return asciiSum(student.studentName) == hashedStudentName;    
}

void printIndexOfStudent (StudentEntry student, int index)
{
    std::cout << student.studentName <<  " found at index " << index << std::endl;
}

void Executive::findStudent()
{
    string studentName;
    cout << "Enter the student to be found: ";
    getline(cin, studentName);

    m_hashtable.traverseTable(compName, asciiSum(studentName), printIndexOfStudent);
}
