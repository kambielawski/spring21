#include "Executive.h"

Executive::Executive (char *fileName)
{
    ifstream infile(fileName);
    if (infile.is_open()) {
        // read file
        bst = new BinarySearchTree<int>();
    } else {
        throw runtime_error("Error opening file");
    }
}

Executive::~Executive () {}

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
    item = this->getInt("Enter item to insert: ", "Couldn't insert item");
    bst->insert(item, item);
}

void Executive::deleteItem()
{

}

void Executive::findMin()
{
    int min = bst->findMin();
    cout << min << " is the minimum item in the tree\n";
}

void Executive::findMax()
{
    int max = bst->findMax();
    cout << max << " is the maximum item in the tree\n";
}

void Executive::deleteMin()
{

}

void Executive::deleteMax()
{

}

void Executive::inorderSuccessor()
{

}

void Executive::levelOrder()
{
    bst->printLevelOrder();    
}

void Executive::spiralLevelOrder()
{

}

void Executive::leftSideView()
{

}

void Executive::rightSideView()
{

}

void Executive::experimentalProfiling()
{

}

