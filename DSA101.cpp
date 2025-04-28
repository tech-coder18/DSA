#include <iostream>
using namespace std;
#define MAX 100

class StudentHeap {
    int marks[MAX];
    int size;

public:
    StudentHeap() {
        size = 0;
    }
    void insert(int mark) {
        size++;
        int i = size;
        marks[i] = mark;
        while (i > 1 && marks[i] < marks[i / 2]) {
            swap(marks[i], marks[i / 2]);
            i = i / 2;
        }
    }
    void display() {
        cout << "\nHeap structure (Min Heap): ";
        for (int i = 1; i <= size; i++) {
            cout << marks[i] << " ";
        }
        cout << endl;
    }
    void findMin() {
        if (size == 0) {
            cout << "No marks entered yet.\n";
            return;
        }
        cout << "Minimum Marks: " << marks[1] << endl; // root of min heap
    }
    void findMax() {
        if (size == 0) {
            cout << "No marks entered yet.\n";
            return;
        }
        int maxMark = marks[1];
        for (int i = 2; i <= size; i++) {
            if (marks[i] > maxMark) {
                maxMark = marks[i];
            }
        }
        cout << "Maximum Marks: " << maxMark << endl;
    }
};

int main() {
    StudentHeap heap;
    int choice, mark, n;
    do {
        cout << "\n--- Menu ---";
        cout << "\n1. Insert Student Marks";
        cout << "\n2. Display Heap";
        cout << "\n3. Find Minimum Marks";
        cout << "\n4. Find Maximum Marks";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "How many marks to enter? ";
            cin >> n;
            for (int i = 0; i < n; i++) {
                cout << "Enter mark " << i + 1 << ": ";
                cin >> mark;
                heap.insert(mark);
            }
            break;
        case 2:
            heap.display();
            break;
        case 3:
            heap.findMin();
            break;
        case 4:
            heap.findMax();
            break;
        case 5:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);
    return 0;
}