#include "Executive.h"

Executive::Executive(char *filename)
{
    ifstream infile(filename);
    if (infile.is_open()) {
        graph = new Graph();
        this->readIntoArray(infile);
    } else {
        throw runtime_error("Couldn't open file");
    }
}

Executive::~Executive()
{

}

void Executive::readIntoArray(ifstream& infile)
{
    int inp;
    string line;

    /* Grab the size */
    getline(infile, line, '\n');
    try {
        graph_size = stoi(line.substr(line.find(',') + 1));
    } catch (exception& e) {
        throw runtime_error("Couldn't read file\n");
    }

    /* Allocate room for size x size array */
    inp_arr = new int*[graph_size];
    for (int i = 0; i < graph_size; i++)
        inp_arr[i] = new int[graph_size];
    
    /* Now read the next lines into the array */
    for (int i = 0; i < graph_size; i++) {
        for (int j = 0; j < graph_size; j++) {
            infile >> inp;
            inp_arr[i][j] = inp;
        }
    }
}

int Executive::getChoice(string prompt) const
{
    int choice;
    cout << prompt;
    cin >> choice;
    while (cin.fail()) {
        cout << "Please enter a number\n";
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

    while (choice != 6) {
        this->printMenu();
        choice = this->getChoice("Enter choice: ");

        switch (choice) {
            case 1: this->buildGraph();
                break;
            case 2: this->breadthFirstSearch();
                break;
            case 3: this->depthFirstSearch();
                break;
            case 4: this->kruskal();
                break;
            case 5: this->prim();
                break;
            case 6: cout << "Exiting...\n";
                return;
            default:
                cout << "Invalid input\n";
                break;

        }
    }
}

void Executive::buildGraph()
{
    graph->buildGraph(inp_arr, graph_size);    
    cout << "Graph has been built successfully\n";    
}

void Executive::breadthFirstSearch()
{

}

void Executive::depthFirstSearch()
{

}

void Executive::kruskal()
{

}

void Executive::prim()
{

}

void Executive::printMenu() const
{
    cout << "=====================\n"
    << "1 - BuildGraph\n"
    << "2 - BFS\n"
    << "3 - DFS\n"
    << "4 - Kruskal\n"
    << "5 - Prim\n"
    << "6 - Exit\n\n";
}
