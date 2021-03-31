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

    string int_str;
    int num;
    while (getline(infile, int_str, ',')) {
        try {
            num = stoi(int_str); 
            heap->insertItem(num, num);
        } catch (exception& e) {
            throw runtime_error("Couldn't read file\n");
        }
    }

    heap->printHeap();
}

Executive::~Executive()
{
    delete heap;
    heap = nullptr;
}

int Executive::getChoice(string prompt) const
{
    int choice;
    cout << prompt;
    cin >> choice;
    while (cin.fail()) {
        cout << "Invalid entry - enter a number\n";
        /* cin.clear() clears the error flags of cin so new I/O operations can work */
        cin.clear();
        cin.ignore(10000, '\n');
        cout << prompt;
        cin >> choice;
    }

    return choice;
}

void Executive::run()
{
    int choice = -1;

    while (choice != 6) {
        this->printMenu();
        choice = this->getChoice("Enter choice: ");
        
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
            case 7: heap->printHeap();
                break;
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
    int newItem = this->getChoice("Enter item to insert: ");

    heap->insertItem(newItem, newItem);

    cout << newItem << " successfully inserted\n";
}

void Executive::deleteMin()
{
    heap->deleteMin();
}

void Executive::printMinLevels() const
{
    heap->printMinLevels();
}

void Executive::printMaxLevels() const
{
    heap->printMaxLevels();
}

void Executive::printMenu() const
{
    cout << "=================\n"
    << "1. Build Heap\n" // Build heap using a top-down approach
    << "2. Insert\n"     // insert item into minmax heap
    << "3. Delete\n"     // delete the root element
    << "4. Min level elements\n" // print only min-level elements (inorder)
    << "5. Max level elements\n" // print only max-level elements
    << "6. Exit\n\n"
    << "7. Print heap\n"; // prints entire heap
}
