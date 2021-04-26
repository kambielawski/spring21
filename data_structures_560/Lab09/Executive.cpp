#include "Executive.h"

static const int MAX_ITEMS = 256;

Executive::Executive(char *filename) : num_items(0), ds(nullptr)
{
    ifstream infile(filename);
    if (infile.is_open()) {
        ds = new DisjointSets<int>();
        num_array = this->readIntoArray(infile);
    } else {
        throw runtime_error("Couldn't open file");
    }
}

Executive::~Executive()
{
    delete ds;
    delete [] num_array;
    ds = nullptr;
}

int* Executive::readIntoArray(ifstream& infile) 
{
    int *arr = new int[MAX_ITEMS];
    int item;
    int index = 0;
    while (infile >> item) {
        arr[index] = item;
        index++;
    }

    num_items = index;
    return arr;
}

void Executive::run()
{
    int choice = -1;
    while (choice != 6) {
        this->printMenu();
        choice = this->getChoice("Enter choice: ");
        switch (choice) {
            case 1: this->makeSet();
                break;
            case 2: this->unionByRank();
                break;
            case 3: this->find();
                break;
            case 4: this->pathCompression();
                break;
            case 5: this->printPath();
                break;
            case 6: cout << "Exiting...\n";
                return;
                break;
            default:
                break; 
        }
    }
}


void Executive::makeSet()
{
    if (num_array == nullptr || num_items == 0)
        throw runtime_error("Couldn't make disjoint sets\n");
    ds->makeSet(num_array, num_items);
    cout << "The disjoint sets have been constructed\n";
}


void Executive::unionByRank()
{
    cout << "Enter the two elements for which sets you want to union:\n";
    int item1 = this->getChoice("Item 1: ");
    int item2 = this->getChoice("Item 2: ");

    try {
        ds->unionByRank(item1, item2);
        int representative_item = ds->findItem(item1);
        cout << "Union on " << item1 << " and " << item2 << " successful.\n"
        << "Representative element is " << representative_item << endl;
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}


void Executive::find()
{
    int item_to_find = this->getChoice("Enter item to find: ");
    try {
        int item = ds->findItem(item_to_find);
        cout << item_to_find << " has been found successfully.\nThe representative item is " << item << endl;
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void Executive::pathCompression()
{
    int pc_item = this->getChoice("Enter item to do path compression on: ");
    try {
        ds->pathCompression(pc_item);
        cout << "Path compression done successfully.\n"
        << "Representative element is " << ds->findItem(pc_item) << endl;
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}


void Executive::printPath()
{
    int path_item = this->getChoice("Enter item whose path you want to print: ");
    try {
        ds->printPath(path_item);
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}


int Executive::getChoice(string prompt) const
{
    int choice;
    cout << prompt;
    cin >> choice;
    while (cin.fail()) {
        cout << "Please enter a number\n";
        cin.ignore(10000, '\n');
        cin.clear();
        cout << prompt;
        cin >> choice;
    }

    return choice;
}

void Executive::printMenu() const
{
    cout << "==============================\n"
    << "Please choose between the following commands:\n"
    << "1 - Make set\n"
    << "2 - UnionByRank\n"
    << "3 - Find\n"
    << "4 - PathCompression\n"
    << "5 - Print Path\n"
    << "6 - Exit\n\n";
}
