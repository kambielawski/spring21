#include "Executive.h"

ostream& operator<<(ostream& os, Restaurant& rhs) {
    os << rhs.name;
}

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
    delete min_heap;
    delete max_heap;
    min_heap = nullptr;
    max_heap = nullptr;
}

void Executive::readFromFile(ifstream& infile)
{
    string line;

    Restaurant* new_restaurant;
  
    /* Read line by line */
    while (getline(infile, line))
    {
        new_restaurant = this->parseRestaurantString(line);
        
        cout << "Inserting " << new_restaurant->name << " " << new_restaurant->distance << " " << new_restaurant->num_reviews << endl;
        min_heap->insert(new_restaurant->distance, *new_restaurant);
        max_heap->insert(new_restaurant->num_reviews, *new_restaurant);

        delete new_restaurant;
    }

    new_restaurant = nullptr;
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

    if (first_comma_index == -1 || last_comma_index == -1)
        throw runtime_error("Invalid input string");

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
                return;
            default:
                break;
        }
    }
}

void Executive::addNewRestaurant()
{
    string input;
    cout << "Enter the record to be inserted:\n";
    cin >> input;

    Restaurant *new_restaurant;

    try {
        new_restaurant = this->parseRestaurantString(input); 
    } catch (exception& e) {
        cout << e.what() << ": must be of form '<name>,<distance>,<review count>'\n";
        cin.ignore(INT_MAX, '\n');
        cin.clear();
        return;
    }
    
    if (min_heap->contains(*new_restaurant) || max_heap->contains(*new_restaurant))
        cout << "Can't insert duplicate restaurant\n";
    else {
        min_heap->insert(new_restaurant->distance, *new_restaurant);
        max_heap->insert(new_restaurant->num_reviews, *new_restaurant);
    }

    // clean memory
    delete new_restaurant;
    new_restaurant = nullptr;
}

void Executive::removeNearest() 
{
    /* Check for empty heap */
    if (min_heap->size() == 0) {
        cout << "No items left to remove\n";
        return;
    }

    Restaurant nearest = min_heap->popRoot(); // remove and return nearest restaurant
    int maxheap_size = max_heap->size();

    /* Recover the heap_array and delete max_heap */
    Restaurant *arr = max_heap->asArray();
    delete max_heap;

    /* Rebuild max_heap w/o inserting nearest */
    max_heap = new K_Ary_Heap<Restaurant>(3, false);
    for (int i = 0; i < maxheap_size; i++) {
        if (!(arr[i] == nearest)) {
            max_heap->insert(arr[i].num_reviews, arr[i]); 
        }
    }

    cout << "Nearest: " << nearest << ": " << nearest.distance << " has been removed\n";

    /* Clean up memory */
    delete[] arr;
    arr = nullptr;
}

void Executive::removeMostReviewed() 
{
    /* Check for empty heap */
    if (max_heap->size() == 0) {
        cout << "No items left to remove\n";
        return;
    }

    Restaurant most_reviewed = max_heap->popRoot(); // remove and return most reviewed restaurant
    int minheap_size = min_heap->size();

    /* Recover the heap_array and delete min_heap */
    Restaurant *arr = min_heap->asArray();
    delete min_heap;

    /* Rebuild max_heap w/o inserting nearest */
    min_heap = new K_Ary_Heap<Restaurant>(3, false);
    for (int i = 0; i < minheap_size; i++) {
        if (!(arr[i] == most_reviewed)) {
            min_heap->insert(arr[i].distance, arr[i]); 
        }
    }

    cout << "Most Reviewed: " << most_reviewed << ": " << most_reviewed.num_reviews << " has been removed\n";

    /* Clean up memory */
    delete[] arr;
    arr = nullptr;
}

void Executive::searchNearest() const
{
    if (min_heap->size() == 0) {
        cout << "Heap is empty\n";
        return;
    }
    Restaurant nearest = min_heap->peekRoot();
    cout << "Nearest restaurant: " << nearest.name << endl;
    cout << "Distance: " << nearest.distance << " miles\n";
}

void Executive::searchMostReviewed() const
{
    if (min_heap->size() == 0) {
        cout << "Heap is empty\n";
        return;
    }
    Restaurant nearest = max_heap->peekRoot();
    cout << "Most reviewed restaurant: " << nearest.name << endl;
    cout << "Reviews: " << nearest.num_reviews << " reviews\n";
}

void Executive::printByDistance() const
{
    min_heap->printLevelOrder();
}

void Executive::printByReviewCount() const
{
    max_heap->printLevelOrder();
}

int Executive::getChoice(string prompt, string onError) const
{
    int choice;
    string choiceStr;

    bool valid = false;
    while (!valid) {
        cout << prompt;
        cin >> choiceStr;
        try {
            choice = stoi(choiceStr);
            valid = true;
        } catch (exception& e) {
            cout << "Error: " << e.what() << endl;
        }
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

