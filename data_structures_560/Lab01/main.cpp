#include <iostream>
#include <fstream>
#include <exception>

#include "Executive.h"

using namespace std;

int main (int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Usage: ./lab1 <input file>\n";
    exit(1);
  }
  
  try {
    Executive exec(argv[1]);
    exec.run();
  } catch (exception& e) {
    cout << "something went wrong: " << e.what() << endl;
  }

  return 0;
}
