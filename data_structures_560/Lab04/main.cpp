#include <iostream>
#include <exception>
#include "Executive.h"
using namespace std;

int main (int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Usage: ./main <inputfile>\n";
        exit(1);
    }

    try {
        Executive exec(argv[1]);
        exec.run();
    } catch (exception& e) {
        cout << "Something went wrong: " << e.what() << endl;
        exit(1);
    }

    return 0;
}
