#include <iostream>
#include <fstream>

#include "Executive.h"

int main (int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: ./Lab01 <filename>\n";
        exit(1);
    }
    
    Executive exec(argv[1]);
    exec.run();

    return 0;
}
