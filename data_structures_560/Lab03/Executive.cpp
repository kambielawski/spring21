#include "Executive.h"

/* 
 * These top two functions will be used as the hash functions for the
 * quadratic probing and double hashing 
 */

Executive::Executive(char *file)
{
    std::ifstream infile(file);

    if (infile.is_open())
    {
        this->readFileIntoTables(infile);
    } else {
        throw std::runtime_error("Error opening file");
    }
}

Executive::~Executive() {}

void Executive::readFileIntoTables(std::ifstream& infile)
{
    std::string numStr;
    int num;
    while (!infile.eof())
    {
        infile >> numStr;
        try {
            num = stoi(numStr);
            // insert into hashtables
        } catch (std::exception& e) {
            throw std::runtime_error("Error reading file (file can only contain numbers)");
        }
    }

    infile.close();
}

void Executive::run()
{
    std::string choiceStr;
    int choice = -1;

    while (choice != 5)
    {
        // Print menu and get choice from user
        this->printMenu();
        std::cout << "Choice: ";
        std::cin >> choiceStr;
        std::cout << "\n";
        try {
            choice = stoi(choiceStr);
        } catch (std::exception& e) {
            std::cout << "Invalid choice. Please choose a number between 1 and 5.\n";
            continue;
        }

        // switch over value of choice
        switch(choice)
        {
            case 1:
                this->insertItem();
                break;
            case 2:
                this->deleteItem();
                break;
            case 3:
                this->findItem();
                break;
            case 4:
                this->printTables();
                break;
            case 5:
                std::cout << "Exiting...\n";
                break;
            default:
                break;
        }
        std::cout << "\n";
    }
}

void Executive::insertItem()
{
    std::cout << "Insert item\n";
}

void Executive::deleteItem()
{
    std::cout << "delete item\n";
}

void Executive::findItem()
{
    std::cout << "find item\n";
}

void Executive::printTables()
{
    std::cout << "print tables\n";
}

void Executive::printMenu() const
{
    std::cout << "=================\n"
    << "Please choose one of the following commands:\n"
    << "1. Insert\n"
    << "2. Delete\n"
    << "3. Find\n"
    << "4. Print\n"
    << "5. Exit\n\n";
}
