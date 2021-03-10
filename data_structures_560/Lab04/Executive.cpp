#include "Executive.h"

Executive::Executive (char *fileName)
{
    ifstream infile(fileName);
    if (infile.is_open()) {
        // read file
        bst = new BinarySearchTree<int>();
        this->readIntoBST(infile);
    } else {
        throw runtime_error("Error opening file");
    }
}

Executive::~Executive () {}

void Executive::readIntoBST (ifstream& infile)
{
    int i;
    string iStr;
    while (infile >> iStr) {
        try {
            i = stoi(iStr);
            bst->insert(i, i);
        } catch (exception& e) {
            throw runtime_error("Error reading from file");
        }
    }
}

void Executive::run ()
{
    int choice = -1;
    string choiceStr;

    while (choice != 13) {
        this->printMenu();
        cout << "Choice: ";
        cin >> choiceStr;
        cout << "\n\n";
        try {
            choice = stoi(choiceStr);
            switch (choice)
            {
                case 1:
                    this->addItem();
                    break;
                case 2:
                    this->deleteItem();
                    break;
                case 3:
                    this->findMin();
                    break;
                case 4:
                    this->findMax();
                    break;
                case 5:
                    this->deleteMin();
                    break;
                case 6:
                    this->deleteMax();
                    break;
                case 7:
                    this->inorderSuccessor();
                    break;
                case 8:
                    this->levelOrder();
                    break;
                case 9:
                    this->spiralLevelOrder();
                    break;
                case 10:
                    this->leftSideView();
                    break;
                case 11:
                    this->rightSideView();
                    break;
                case 12:
                    this->experimentalProfiling();
                    break;
                case 13:
                    cout << "Exiting...\n";
                    exit(0);
                    break;
                case 14:
                    this->inorderPrint();
                    break;
                case 15:
                    this->preorderPrint();
                    break;
                case 16:
                    this->postorderPrint();
                    break;
                default:
                    break;
            }
        } catch (exception& e) {
            cout << "Error: " << e.what() << endl;
            cout << "Please enter a number between 1 and 13\n";
        }
    }
}

void Executive::printMenu () const
{
    cout << "===================\n"
    << "1. AddItem\n"
    << "2. DeleteItem\n"
    << "3. FindMin\n"
    << "4. FindMax\n"
    << "5. DeleteMin\n"
    << "6. DeleteMax\n"
    << "7. InorderSuccessor\n"
    << "8. LevelOrder\n"
    << "9. SpiralLevelOrder\n"
    << "10. LeftSideView\n"
    << "11. RightSideView\n"
    << "12. ExperimentalProfiling\n"
    << "13. Exit\n\n";
}

int Executive::getInt(string prompt, string onError) const
{
    int i;
    string iStr;
    bool invalid = true;

    cout << prompt;
    cin >> iStr;

    while (invalid) {
        try {
            i = stoi(iStr);
            invalid = false;
        } catch (exception& e) {
            cout << "Error: " << onError << endl;
        }
    }

    return i;
}

void Executive::addItem()
{
    int item;
    item = this->getInt("Enter item to insert: ", "Invalid input");
    bst->insert(item, item);
}

void Executive::deleteItem()
{
    int itemToDelete = this->getInt("Enter item to delete: ", "Invalid input");
    try {
        bst->remove(itemToDelete);
        cout << "Successfully deleted " << itemToDelete << endl;
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }

}

void Executive::findMin()
{
    try {
        int min = bst->findMin();
        cout << min << " is the minimum item in the tree\n";
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void Executive::findMax()
{
    try {
        int max = bst->findMax();
        cout << max << " is the maximum item in the tree\n";
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void Executive::deleteMin()
{
    try {
        bst->deleteMin();
        cout << "Smallest element was successfully deleted from the tree\n";
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void Executive::deleteMax()
{
    try {
        bst->deleteMax();
        cout << "Largest element was successfully deleted from the tree\n";
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void Executive::inorderSuccessor()
{
    cout << "** Could not finish before deadline **\n\n";
}

void Executive::levelOrder()
{
    bst->printLevelOrder();    
}

void Executive::spiralLevelOrder()
{
    cout << "** Could not finish before deadline **\n\n";
}

void Executive::leftSideView()
{
    cout << "** Could not finish before deadline **\n\n";
}

void Executive::rightSideView()
{
    cout << "** Could not finish before deadline **\n\n";
}

float Executive::profileBuild(int size)
{
    clock_t t;
    int item, j;
    // iterate over input sizes
    srand(time(NULL)); 
    t = clock();  
    for (int j = size; j > 0; j--) {
        item = rand() * 100 % 500000 + 1;
        profileTree->insert(item, item);
    }
    t = clock() - t;
    return t;
}
float Executive::profileFindMin(int size)
{
    clock_t t;
    t = clock();  
    profileTree->findMin();
    t = clock() - t;
    return t;
}
float Executive::profileFindMax(int size)
{
    clock_t t;
    // iterate over input sizes
    t = clock();  
    profileTree->findMax();
    t = clock() - t;
    return t;
}
float Executive::profileDeleteMin(int size)
{
    clock_t t;
    t = clock();  
    profileTree->deleteMin();
    t = clock() - t;
    return t;
}
float Executive::profileDeleteMax(int size)
{
    clock_t t;
    t = clock();  
    profileTree->deleteMax();
    t = clock() - t;
    return t;
}

void Executive::experimentalProfiling()
{
    float avgBuildTimes[5] = { 0, 0, 0, 0, 0 };
    float avgFindMinTimes[5] = { 0, 0, 0, 0, 0 };
    float avgFindMaxTimes[5] = { 0, 0, 0, 0, 0 };
    float avgDeleteMinTimes[5] = { 0, 0, 0, 0, 0 };
    float avgDeleteMaxTimes[5] = { 0, 0, 0, 0, 0 };

    int i, j;
    // 5 different seeds
    for (j = 0; j < 5; j++) {
        srand(time(NULL));
        // iterate over sizes
        for (i = 10000; i <= 50000; i += 10000) {
            profileTree = new BinarySearchTree<int>();

            avgBuildTimes[i/10000 - 1] += profileBuild(i);
            avgFindMinTimes[i/10000 - 1] += profileFindMin(i);
            avgFindMaxTimes[i/10000 - 1] += profileFindMax(i);
            avgDeleteMinTimes[i/10000 - 1] += profileDeleteMin(i);
            avgDeleteMaxTimes[i/10000 - 1] += profileDeleteMax(i);

            delete profileTree;
        }
    }
    // average the measurements
    for (i = 0; i < 5; i++) {
        avgBuildTimes[i] /= 5.0 * CLOCKS_PER_SEC;
        avgFindMinTimes[i] /= 5.0 * CLOCKS_PER_SEC;
        avgFindMaxTimes[i] /= 5.0 * CLOCKS_PER_SEC;
        avgDeleteMinTimes[i] /= 5.0 * CLOCKS_PER_SEC;
        avgDeleteMaxTimes[i] /= 5.0 * CLOCKS_PER_SEC;
    }
    cout << "Input Size\t10,000\t20,000\t30,000\t40,000\t50,000\n";
    cout << "Build(s)\t" << avgBuildTimes[0] << "\t" << avgBuildTimes[1] << "\t" << avgBuildTimes[2]<< "\t" << avgBuildTimes[3]<< "\t" << avgBuildTimes[4] << endl;
    cout << "Find Min\t" << avgFindMinTimes[0] << "\t" << avgFindMinTimes[1] << "\t" << avgFindMinTimes[2]<< "\t" << avgFindMinTimes[3]<< "\t" << avgFindMinTimes[4] << endl;
    cout << "Find Max\t" << avgFindMaxTimes[0] << "\t" << avgFindMaxTimes[1] << "\t" << avgFindMaxTimes[2]<< "\t" << avgFindMaxTimes[3]<< "\t" << avgFindMaxTimes[4] << endl;
    cout << "Delete Min\t" << avgDeleteMinTimes[0] << "\t" << avgDeleteMinTimes[1] << "\t" << avgDeleteMinTimes[2]<< "\t" << avgDeleteMinTimes[3]<< "\t" << avgDeleteMinTimes[4] << endl;
    cout << "Delete Max\t" << avgDeleteMaxTimes[0] << "\t" << avgDeleteMaxTimes[1] << "\t" << avgDeleteMaxTimes[2]<< "\t" << avgDeleteMaxTimes[3]<< "\t" << avgDeleteMaxTimes[4] << endl;
}

void Executive::preorderPrint()
{
    bst->preorderPrint();
}
void Executive::inorderPrint()
{
    bst->inorderPrint();
}
void Executive::postorderPrint()
{
    bst->postorderPrint();
}
