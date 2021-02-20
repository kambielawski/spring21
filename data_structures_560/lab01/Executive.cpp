#include "Executive.h"
#include <exception>

Executive::Executive(char *fileName)
{
    m_infile.open(fileName);
    if (m_infile.is_open())
        this->readFileIntoList();
    else
        throw std::runtime_error("Error opening file\n");
}

Executive::~Executive() {}

/* called from main */
void Executive::run ()
{
    int choice;
    
    do {
        this->printMenu();
        choice = this->getValidChoice();

        switch (choice)
        {
            case 1:
                this->getIsEmpty();
                break;
            case 2:
                this->getLength();
                break;
            case 3:
                this->insertItem();
                break;
            case 4:
                this->deleteItem();
                break;
            case 5:
                this->find(); 
                break;
            case 6:
                this->findPrev();
                break;
            case 7:
                this->appendList();
                break;
            case 8:
                this->forwardTraverse();
                break;
            case 9:
                this->backwardTraverse();
                break;
            case 10:
                std::cout << "Exiting...\n"
                << "=================\n";
            default:
                break;
        }
        
    } while (choice != 10);

}

void Executive::getIsEmpty()
{
    std::cout << "IsEmpty: ";
    if (list.isEmpty())
        std::cout << "True\n";
    else
        std::cout << "False\n";
}

void Executive::getLength()
{
    std::cout << "Length: " << list.length() << std::endl;
}

void Executive::insertItem()
{
    int newItem = this->getValidNum("Enter item to insert: ", "Entry must be a number");
    list.insertItem(newItem);
    std::cout << newItem << " successfully inserted.\n";
}

void Executive::deleteItem()
{
    int itemToDelete = this->getValidNum("Enter item to delete: ", "Entry must be a number");
    if (list.find(itemToDelete))
        list.deleteItem(itemToDelete);
    else
        std::cout << itemToDelete << " is not in the list\n";
}

void Executive::find()
{
    int val = this->getValidNum("Enter item to find: ", "Entry must be a number");
    std::cout << val << " is ";
    if (list.find(val) == -1)
        std::cout << "not ";
    std::cout << "in the list.\n";
}

void Executive::findPrev()
{
    int indexOfItem;
    int itemToFind = this->getValidNum("Enter item to find: ", "Entry must be a number");
    if ((indexOfItem = list.find(itemToFind)) != -1)
    {
        if (indexOfItem == 0)
            std::cout << "None\n";
        else
            std::cout << list.getItemAtIndex(indexOfItem - 1) << " is previous to " << itemToFind << std::endl;
    }
    else
    {
        std::cout << itemToFind << " not in list.\n";
    }
}

void Executive::appendList()
{
    std::string listStr;
    
    std::cout << "Enter the list: ";
    std::cin.ignore();
    std::getline(std::cin, listStr);
    this->trimWhitespace(&listStr);

    std::string currentNumStr;
    int currentNum;
    int end;
    bool done = false;
    while (!done) // string.find() method returns std::string::npos if nothing found
    {
        end = listStr.find(' ');
        if (end == std::string::npos)
            done = true; 
        currentNumStr = listStr.substr(0, end);
        try
        {
            currentNum = stoi(currentNumStr);
            list.insertItem(currentNum);
        }
        catch (std::exception& e)
        {
            std::cout << "Error parsing list" << std::endl;
            return;
        }
        listStr = listStr.substr(end+1);
    }
    std::cin.clear();
    std::cout << "List appended.\n"; 
}

void Executive::trimWhitespace(std::string* str)
{
    while (str->at(0) == ' ')
        *str = str->substr(1);
    while (str->at(str->length() - 1) == ' ')
        *str = str->substr(0, str->length() - 1);
}

void Executive::forwardTraverse() 
{
    std::cout << "Forward traverse: ";
    for (int i = 0; i < list.length(); i++)
        std::cout << list.getItemAtIndex(i) << " ";
    std::cout << "\n";
}

void Executive::backwardTraverse() 
{
    std::cout << "Backward traverse: ";
    for (int i = list.length() - 1; i >= 0; i--)
        std::cout << list.getItemAtIndex(i) << " ";
    std::cout << "\n";
}

void Executive::readFileIntoList()
{
    std::string numStr;
    int num;
    while (m_infile >> numStr)
    {
        try
        {
            num = stoi(numStr);
            list.insertItem(num);
        }
        catch (std::exception& e)
        {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    m_infile.close();
}

int Executive::getValidChoice() const
{
    std::string choiceStr;
    int choice = -1;
    while (!(choice <= 10 && choice >= 1))
    {
        std::cout << "Enter choice: ";
        std::cin >> choiceStr;
        try
        {
            choice = stoi(choiceStr);
        }
        catch (std::exception& e)
        {
            std::cout << "Pick a number between 1 and 10\n";
        }
    }
    return choice;
}

int Executive::getValidNum(std::string prompt, std::string onError) const
{
    std::string valueStr;
    int value;
    bool valid = false;
    while (!valid)
    {
        std::cout << prompt;
        std::cin >> valueStr;
        try
        {
            value = stoi(valueStr);
            valid = true;
        }
        catch (std::exception& e)
        {
            std::cout << "Error: " << onError << std::endl;
        }
    }
    return value;
}

void Executive::printMenu () const
{
    std::cout << "=================\n"
    << "Choose one operation from the options below:\n"
    << "1. IsEmpty\n"
    << "2. Length\n"
    << "3. Insert\n"
    << "4. Delete\n"
    << "5. Find\n"
    << "6. FindPrev\n"
    << "7. AppendList\n"
    << "8. Forward Traverse\n"
    << "9. Backward Traverse\n"
    << "10. Exit\n\n";
}
