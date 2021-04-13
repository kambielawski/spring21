#include <iostream>
#include "Executive.h"
using namespace std;

int main (int argc, char *argv[])
{
    if (argc < 2) {
        cout << "Usage: ./main <input file>\n";
        exit(EXIT_FAILURE);
    }

    try {
        Executive exec(argv[1]);
        exec.run();
    } catch (exception& e) {
        cout << "Error occurred: " << e.what() << endl;
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
