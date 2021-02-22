#include "Executive.h"

/* 
 * These top two functions will be used as the hash functions for the
 * quadratic probing and double hashing 
 */

int doubleHashing (int searchKey, int hash_i)
{
    const int R = 5;
    return (searchKey + hash_i*(R - (searchKey % R)));
}

int quadraticProbing (int searchKey, int hash_i)
{
    return (searchKey + std::pow(hash_i, 2)); 
}

/*
 * Executive class methods
*/

Executive::Executive(char *file)
{
    std::ifstream infile(file);

    if (infile.is_open())
    {
        // create hash tables
        this->doubleHashingTable = new HashTable<int>(quadraticProbing);
        this->quadraticProbingTable = new HashTable<int>(doubleHashing);

        // read file content into tables
        this->readFileIntoTables(infile);
    } else {
        throw std::runtime_error("Error opening file");
    }
}

Executive::~Executive() {
    delete quadraticProbingTable;
    quadraticProbingTable = nullptr;
    delete doubleHashingTable;
    doubleHashingTable = nullptr;
}

void Executive::readFileIntoTables(std::ifstream& infile)
{
    std::string numStr;
    int num;
    while (infile >> numStr)
    {
        try {
            num = stoi(numStr);
            // insert into hashtables
            doubleHashingTable->insert(num, num);
            quadraticProbingTable->insert(num, num);
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
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
    std::string numStr;
    int num;
    std::cout << "Enter item to insert: ";
    std::cin >> numStr;
    try
    {
        num = stoi(numStr);
        quadraticProbingTable->insert(num, num);
        doubleHashingTable->insert(num, num);
    } catch (std::exception& e) {
        std::cout << "Couldn't insert item: " << e.what() << std::endl;
    }
}

void Executive::deleteItem()
{
    std::string numStr;
    int num;
    std::cout << "Enter item to delete: ";
    std::cin >> numStr;
    try
    {
        num = stoi(numStr);
        std::cout << "Quadratic Probing:\n\n";
        if (quadraticProbingTable->remove(num, num))
            std::cout << num << " is deleted\n\n";
        else
            std::cout << num << " couldn't be deleted\n\n";

        std::cout << "Double Hashing:\n\n";
        if (doubleHashingTable->remove(num, num))
            std::cout << num << " is deleted\n\n";
        else
            std::cout << num << " couldn't be deleted\n\n";
    } catch (std::exception& e) {
        std::cout << "Couldn't insert item: " << e.what() << std::endl;
    }
}

void Executive::findItem()
{
    std::string numStr;
    int num;
    std::cout << "Enter item to find: ";
    std::cin >> numStr;
    std::cout << std::endl;
    try
    {
        num = stoi(numStr);
        std::cout << "Quadratic Probing:\n\n";
        if (quadraticProbingTable->contains(num, num))
            std::cout << num << " is found\n\n";
        else
            std::cout << num << " is not found\n\n";

        std::cout << "Double Hashing:\n\n";
        if (doubleHashingTable->contains(num, num))
            std::cout << num << " is found\n\n";
        else
            std::cout << num << " is not found\n\n";
    } catch (std::exception& e) {
        std::cout << "Couldn't insert item: " << e.what() << std::endl;
    }
}

void Executive::printTables()
{
    std::cout << "Quadratic Probing Table\n";
    quadraticProbingTable->printTable();
    std::cout << "\nDouble Hashing Table\n";
    doubleHashingTable->printTable();
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
