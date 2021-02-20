#include <fstream>
#include "Executive.h"
using namespace std;

int main (int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Usage: ./main <inputfile>\n";
    exit(1);
  }

  ifstream infile(argv[1]);
  if (infile.is_open()) {
    Executive exec(infile);
    exec.run();
  } else { 
    cout << "Error opening file " << argv[1] << endl;
    exit(1);
  }

  return 0;
}
