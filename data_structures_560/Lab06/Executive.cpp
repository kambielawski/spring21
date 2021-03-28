#include "Executive.h"

Executive::Executive(char *filename)
{
    ifstream infile(filename);
    if (infile.is_open()) {
        this->readIntoHeap(infile);
    } else {
        throw runtime_error("Couldn't open file");
    }
}

void Executive::readIntoHeap(ifstream& infile)
{
    heap = new MinMaxHeap<int>();
}

Executive::~Executive()
{

}

int Executive::getChoice() const
{
    int choice;
    cout << "Enter choice: ";
    cin >> choice;
    while (cin.fail()) {
        cout << "Invalid entry - enter a number\n";
        /* cin.clear() clears the error flags of cin so new I/O operations can work */
        cin.clear();
        cin >> choice;
    }

    return choice;
}

void Executive::run()
{
    int choice = -1;

    while (choice != 6) {
        this->printMenu();
        choice = this->getChoice();
        
        switch (choice) {
            case 1: this->buildHeap();
                break;
            case 2: this->insertItem();
                break;
            case 3: this->deleteMin(); 
                break;
            case 4: this->printMinLevels(); 
                break;
            case 5: this->printMaxLevels(); 
                break;
            case 6: cout << "Exiting...\n";
                return;
            default: cout << "Invalid entry. Enter 1-6\n";
                break;
        }
    }
}

void Executive::buildHeap()
{

}

void Executive::insertItem()
{

}

void Executive::deleteMin()
{

}

void Executive::printMinLevels() const
{

}

void Executive::printMaxLevels() const
{

}

void Executive::printMenu() const
{
    cout << "=================\n"
    << "1. Build Heap\n" // Build heap using a top-down approach
    << "2. Insert\n"     // insert item into minmax heap
    << "3. Delete\n"     // delete the root element
    << "4. Min level elements\n" // print only min-level elements (inorder)
    << "5. Max level elements\n" // print only max-level elements
    << "6. Exit\n\n";
}
