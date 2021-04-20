#include "Executive.h"

Executive::Executive(char *filename)
{
    file_name = filename;
    ifstream infile(filename);
    if (infile.is_open()) {
        heap = new LeftistHeap<int>();
        this->readIntoHeap(infile, heap);
    } else {
        throw runtime_error("Couldn't open file");
    }
}

Executive::~Executive()
{
    delete heap;
    heap = nullptr;
}

void Executive::readIntoHeap(ifstream& infile, LeftistHeap<int> *heap)
{
    int num;
    string int_str;

    while (getline(infile, int_str, ',')) {
        try {
            num = stoi(int_str);
            heap->insert(num, num);
        } catch (exception& e) {
            throw runtime_error("Couldn't read file\n");
        }
    }

    infile.close();
}

void Executive::run()
{
    int choice = -1;

    while (choice != 8) {
        this->printMenu();
        choice = this->getChoice("Enter choice: ");
        switch(choice) {
            case 1: this->buildHeap();
                break;
            case 2: this->insertItem();
                break;
            case 3: this->concatenate();
                break;
            case 4: this->deleteMin();
                break;
            case 5: this->findMin(); 
                break;
            case 6: this->inorderTraversal();
                break;
            case 7: this->levelOrderTraversal();
                break;
            case 8:
                cout << "Exiting...\n";
                return;
            case 9: this->test();
            default:
                break;
        }
    }
}

void Executive::buildHeap()
{
    cout << "Building tree from " << file_name << endl;

    delete heap;
    heap = new LeftistHeap<int>();

    ifstream infile(file_name);
    this->readIntoHeap(infile, heap);

    cout << "Done.\n";
}

void Executive::insertItem()
{
    int num = this->getChoice("Enter the number to insert: ");
    try {
        heap->insert(num, num);
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void Executive::test()
{
    LeftistHeap<int> A;
    A.insert(2, 2);
    A.insert(5, 5);

    A.levelOrderTraversal();
}

void Executive::concatenate()
{
    cout << "Enter the three numbers for heap B:\n";
    int n1 = this->getChoice("Num 1: ");
    int n2 = this->getChoice("Num 2: ");
    int n3 = this->getChoice("Num 3: ");

    heap->insertSideHeap(n1, n1);
    heap->insertSideHeap(n2, n2);
    heap->insertSideHeap(n3, n3);

    heap->mergeSideHeap();
    cout << "Heap successfully merged, new level-order traversal is:\n";
    heap->levelOrderTraversal();

}

void Executive::deleteMin()
{
    try {
        int min = heap->deleteMin();
        cout << min << " has been deleted\n";
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void Executive::findMin()
{
    try {
        int min = heap->findMin();
        cout << min << " is the minimum element\n";
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void Executive::inorderTraversal() const
{
    cout << "Inorder Traversal:\n";
    heap->inorderTraversal();
}

void Executive::levelOrderTraversal() const
{
    cout << "Level order traversal:\n";
    heap->levelOrderTraversal();
}

int Executive::getChoice(string prompt) const
{
    int choice;
    cout << prompt;
    cin >> choice;
    while (cin.fail()) {
        cout << "Invalid entry - enter a number\n";
        cin.clear(); // clears any cin error flags (so new I/O can work)
        cin.ignore(10000, '\n');
        cout << prompt;
        cin >> choice;
    }   
    
    return choice;
}

void Executive::printMenu() const
{
    cout << "===================\n"
    << "1 - BuildHeap\n"
    << "2 - Insert\n"
    << "3 - Concatenate\n"
    << "4 - DeleteMin\n"
    << "5 - FindMin\n"
    << "6 - Inorder\n"
    << "7 - LevelOrder\n"
    << "8 - Exit\n\n";
}
