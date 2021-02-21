#include <iostream>

#include "Executive.h"

int main (int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: ./lab03 <input file>\n";
        exit(EXIT_FAILURE);
    }

    try
    {
        Executive exec(argv[1]);
        exec.run();
    } 
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}
