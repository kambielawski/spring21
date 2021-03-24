#include <iostream>
#include <string>
#include <fstream>
#include <climits>

#include "K_Ary_Heap.h"

using namespace std;

struct Restaurant {
    string name;
    float distance;
    int num_reviews;

    bool operator==(const Restaurant& rhs) {
        return (name == rhs.name);
    }
};

ostream& operator<<(ostream&, Restaurant&);

#ifndef EXECUTIVE_H
#define EXECUTIVE_H

class Executive
{
private:
K_Ary_Heap<Restaurant>* min_heap;
K_Ary_Heap<Restaurant>* max_heap;

int getChoice(string prompt, string onError) const;
void printMenu() const;
void readFromFile(ifstream& infile);
Restaurant* parseRestaurantString(string line) const;

/* Menu options */
void addNewRestaurant();
void removeNearest();
void removeMostReviewed();
void searchNearest() const;
void searchMostReviewed() const;
void printByDistance() const;
void printByReviewCount() const;

public:
Executive(char *file_name);
~Executive();
void run();


};

#endif
