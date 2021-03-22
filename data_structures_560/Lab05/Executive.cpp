#include "Executive.h"

Executive::Executive(char *filename)
{
    ifstream infile(filename);
    if (infile.is_open()) {
        min_heap = new K_Ary_Heap<Restaurant>(3, true);
        max_heap = new K_Ary_Heap<Restaurant>(3, false);
        this->readFromFile(infile);
    } else {
        throw runtime_error("Failed to open input file\n");
    }
}

Executive::~Executive()
{

}

void Executive::readFromFile(ifstream& infile)
{
    string line;

    Restaurant* new_restaurant;
  

    /* Read line by line */
    while (getline(infile, line))
    {
        new_restaurant = this->parseRestaurantString(line);
        
        min_heap->insert(new_restaurant->distance, *new_restaurant);
        max_heap->insert(new_restaurant->num_reviews, *new_restaurant);
    }
}

Restaurant* Executive::parseRestaurantString(string line) const
{
    string restaurant_name;
    float distance;
    int num_reviews;
    int first_comma_index, last_comma_index;

    Restaurant* r = new Restaurant;

    first_comma_index = line.find_first_of(",");
    last_comma_index = line.find_last_of(",");

    r->name = line.substr(0, first_comma_index);
    r->distance = stof(line.substr(first_comma_index+1, last_comma_index - first_comma_index));
    r->num_reviews = stoi(line.substr(last_comma_index+1));

    return r;
}

void Executive::run() 
{
    int choice = -1;
    while (choice != 8) {
        this->printMenu();
        choice = this->getChoice("Enter choice: ", "Invalid choice, pick a number between 1-8");
         
        switch(choice) {
            case 1:
                this->addNewRestaurant();
                break;
            case 2:
                this->removeNearest();
                break;
            case 3:
                this->removeMostReviewed();
                break;
            case 4:
                this->searchNearest();
                break;
            case 5:
                this->searchMostReviewed();
                break;
            case 6:
                this->printByDistance();
                break;
            case 7:
                this->printByReviewCount();
                break;
            case 8:
                cout << "Exiting...\n";
                exit(0);
            default:
                break;
        }
    }
}

void Executive::addNewRestaurant() const
{
     
}

void Executive::removeNearest() const
{

}

void Executive::removeMostReviewed() const
{

}

void Executive::searchNearest() const
{

}

void Executive::searchMostReviewed() const
{

}

void Executive::printByDistance() const
{

}

void Executive::printByReviewCount() const
{

}

int Executive::getChoice(string prompt, string onError) const
{
    int choice;
    string choiceStr;

    cout << prompt;
    cin >> choiceStr;

    try {
        choice = stoi(choiceStr);
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return choice;
}

void Executive::printMenu() const
{
    cout << "=======================\n"
    << "1. Add new restaurant\n"
    << "2. Remove nearest restaurant\n"
    << "3. Remove most reviewed restaurant\n"
    << "4. Search nearest restaurant\n"
    << "5. Search most reviewed restaurant\n"
    << "6. Print by restaurant distance\n"
    << "7. Print by restaurant review count\n"
    << "8. Exit\n";
}

