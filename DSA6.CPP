#include <iostream>
using namespace std;

class FlightGraph {
    int cost[20][20], numCities, i, j;
    string cities[20];

public:
    void input();
    void display();
};

void FlightGraph::input() {
    cout << "========== INPUT FLIGHT PATHS ==========" << endl;
    cout << "Enter number of cities (airports): ";
    cin >> numCities;
    cout << "\nEnter names of the cities:\n";
    for (i = 0; i < numCities; i++) {
        cout << "City " << i + 1 << ": ";
        cin >> cities[i];
    }
    for (i = 0; i < numCities; i++)
        for (j = 0; j < numCities; j++)
            cost[i][j] = 0;
    int flights;
    cout << "\nEnter number of direct flights: ";
    cin >> flights;
    string src, dest;
    int srcIndex, destIndex, flightCost;
    for (int f = 0; f < flights; f++) {
        cout << "\nFlight " << f + 1 << ":\n";
        cout << "Source city: ";
        cin >> src;
        cout << "Destination city: ";
        cin >> dest;
        cout << "Cost (Time/Fuel): ";
        cin >> flightCost;
        for (i = 0; i < numCities; i++) {
            if (cities[i] == src)
                srcIndex = i;
            if (cities[i] == dest)
                destIndex = i;
        }
        cost[srcIndex][destIndex] = flightCost;
    }
}

void FlightGraph::display() {
    cout << "\n========== FLIGHT PATH COST MATRIX ==========" << endl;
    cout << "\t";
    for (i = 0; i < numCities; i++) {
        cout << cities[i] << "\t";
    }
    cout << endl;
    for (i = 0; i < numCities; i++) {
        cout << cities[i] << "\t";
        for (j = 0; j < numCities; j++) {
            cout << cost[i][j] << "\t";
        }
        cout << endl;
    }
}

int main() {
    FlightGraph fg;
    int choice;
    do {
        cout << "\n========== FLIGHT GRAPH MENU ==========" << endl;
        cout << "1. Input Flight Data\n";
        cout << "2. Display Adjacency Matrix\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                fg.input();
                break;
            case 2:
                fg.display();
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 3);
    return 0;
}