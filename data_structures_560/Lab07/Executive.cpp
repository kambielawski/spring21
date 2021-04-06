#include "Executive.h"

Executive::Executive(char *filename)
{
    file = filename;
    ifstream infile(filename);
    if (infile.is_open()) {
        heap = new MinMaxHeap<int>();
        this->readIntoHeap(infile);
    } else {
        throw runtime_error("Couldn't open file");
    }
}

Executive::~Executive()
{
    delete heap;
    heap = nullptr;
}

void Executive::readIntoHeap(ifstream& infile)
{
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

    while (choice != 9) {
        this->printMenu();
        choice = this->getChoice("Enter choice: ");
        
        switch (choice) {
            case 1: this->buildHeap();
                break;
            case 2: this->insertItem();
                break;
            case 3: this->deleteMin(); 
                break;
            case 4: this->deleteMax();
                break;
            case 5: this->findMin(); 
                break;
            case 6: this->findMax(); 
                break;
            case 7: heap->printHeap();
                break;
            case 8: this->experimentalProfiling();
                break;
            case 9: cout << "Exiting...\n";
                return;
            default: cout << "Invalid entry. Enter 1-9\n";
                break;
        }
    }
}

void Executive::buildHeap()
{
    ifstream infile(file);
    if (infile.is_open()) {
        while (!heap->isEmpty())
            heap->deleteMin();
        this->readIntoHeap(infile);
    } else {
        throw runtime_error("Couldn't reopen file");
    }

    heap->printHeap();
}

void Executive::insertItem()
{
    int newItem = this->getChoice("Enter item to insert: ");

    heap->insertItem(newItem, newItem);

    cout << newItem << " successfully inserted\n";
}

void Executive::findMin()
{
    cout << "Minimum element is " << heap->findMin() << endl;
}

void Executive::findMax()
{
    cout << "Maximum element is " << heap->findMax() << endl;
}

void Executive::deleteMin()
{
    try {
        heap->deleteMin();
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void Executive::deleteMax()
{
    try {
        heap->deleteMax();
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void Executive::printMinLevels() const
{
    heap->printMinLevels();
}

void Executive::printMaxLevels() const
{
    heap->printMaxLevels();
}

void Executive::experimentalProfiling()
{
    
}

void Executive::printMenu() const
{
    cout << "=================\n"
    << "1. Build Heap\n" // Build heap using a top-down approach
    << "2. Insert\n"     // insert item into minmax heap
    << "3. Delete Min\n"     // delete the root element
    << "4. Delete Max\n"         // deletes maximum node
    << "5. Find Min\n"           // returns min node
    << "6. Find Max\n"           // returns max node
    << "7. Level Order\n"        // prints heap
    << "8. Experimental Profiling\n" // experimental profiling
    << "9. Exit\n\n";
}
