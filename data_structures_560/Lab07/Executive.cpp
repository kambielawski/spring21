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
            case 1: this->buildHeapFromFile();
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

void Executive::clearHeap()
{
    while (!heap->isEmpty()) {
        heap->deleteMin();
    }   
}

/* assumes heap is empty */
void Executive::buildRandomHeap(int num_items)
{
    /* now insert random numbers into heap */
    srand(time(NULL)); 

    int item, j;
    for (j = 0; j < num_items; j++) {
        item = rand() * 100 % 500000;
        heap->insertItem(item, item);
    }
}

void Executive::buildHeapFromFile()
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
    float times[5][5];
    int i;
    
    cout << "==================================\n"
    << "Profiling (profiling w/ valgrind takes significantly longer\n"
    << "===================================\n";

    for (i = 0; i < 5; i++) {
        times[0][i] = this->timeBuildHeap((i+1) * 100000);
        times[1][i] = this->timeFindMin((i+1) * 100000);
        times[2][i] = this->timeFindMax((i+1) * 100000);
        times[3][i] = this->timeDeleteMin((i+1) * 100000);
        times[4][i] = this->timeDeleteMax((i+1) * 100000);
    }

    /* divide CPU times by clocks_per_sec */
    for (i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            times[i][j] /= CLOCKS_PER_SEC;
    }

    cout << "Input Size\t100,000\t200,000\t300,000\t400,000\t500,000\n";
    cout << "BuildHeap\t";
    for (i = 0; i < 5; i++)
        cout << times[0][i] << "\t";

    cout << "\nFindMin  \t";
    for (i = 0; i < 5; i++)
        cout << times[1][i] << "\t";

    cout << "\nFindMax  \t";
    for (i = 0; i < 5; i++)
        cout << times[2][i] << "\t";
        
    cout << "\nDeleteMin\t";
    for (i = 0; i < 5; i++)
        cout << times[3][i] << "\t";

    cout << "\nDeleteMax\t";
    for (i = 0; i < 5; i++)
        cout << times[4][i] << "\t";

    cout << "\n\n";
}

/* TIMING FUNCTIONS */
float Executive::timeBuildHeap(int num_items)
{
    /* clear contents of heap */
    this->clearHeap();

    clock_t t;
    t = clock();
    this->buildRandomHeap(num_items);
    t = clock() - t;

    return t;
}

float Executive::timeDeleteMin(int num_items)
{
    /* clear heap & ensure heap is proper size */
    this->clearHeap();   
    this->buildRandomHeap(num_items);

    /* now time deletes */
    int i;
    clock_t t;
    t = clock();
    for (i = 0; i < num_items; i++) {
        heap->deleteMin();
    }
    t = clock() - t;

    return t;
}

float Executive::timeDeleteMax(int num_items)
{
    /* clear heap & ensure heap is proper size */
    this->clearHeap();   
    this->buildRandomHeap(num_items);

    /* now time deletes */
    int i;
    clock_t t;
    t = clock();
    for (i = 0; i < num_items; i++) {
        heap->deleteMax();
    }
    t = clock() - t;

    return t;
}

float Executive::timeFindMin(int num_items)
{
    /* clear heap & ensure heap is proper size */
    this->clearHeap();   
    this->buildRandomHeap(num_items);

    /* now time deletes */
    int i;
    clock_t t;
    t = clock();
    for (i = 0; i < num_items; i++) {
        heap->findMin();
    }
    t = clock() - t;

    return t;
}

float Executive::timeFindMax(int num_items)
{
    /* clear heap & ensure heap is proper size */
    this->clearHeap();   
    this->buildRandomHeap(num_items);

    /* now time deletes */
    int i;
    clock_t t;
    t = clock();
    for (i = 0; i < num_items; i++) {
        heap->findMax();
    }
    t = clock() - t;

    return t;
}

/* MENU FUNCTION */
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
