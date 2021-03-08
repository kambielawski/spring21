#include "Executive.h"

Executive::Executive (char *fileName)
{
    ifstream infile(fileName);
    if (infile.is_open()) {
        // read file
        cout << "tis opened" << endl;
    } else {
        throw runtime_error("Error opening file");
    }
}

Executive::~Executive () {}

void Executive::run ()
{
    cout << "running" << endl;
}
