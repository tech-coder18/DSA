#include <iostream>
#include <string>
using namespace std;

struct Node {
    string label;
    int childCount;
    Node* children[10];
};

class BookTree {
    Node* root;
public:
    BookTree() {
        root = nullptr;
    }
    void create() {
        root = new Node;
        cout << "Enter book title: ";
        cin.ignore();
        getline(cin, root->label);
        cout << "Enter number of chapters: ";
        cin >> root->childCount;
        for (int i = 0; i < root->childCount; i++) {
            root->children[i] = new Node;
            cout << "  Enter name of Chapter " << i + 1 << ": ";
            cin.ignore();
            getline(cin, root->children[i]->label);
            cout << "  Enter number of sections in Chapter \"" << root->children[i]->label << "\": ";
            cin >> root->children[i]->childCount;
            for (int j = 0; j < root->children[i]->childCount; j++) {
                root->children[i]->children[j] = new Node;
                cout << "    Enter name of Section " << j + 1 << ": ";
                cin.ignore();
                getline(cin, root->children[i]->children[j]->label); 
                cout<< "        Enter the number of Subsections \"" <<root->children[i]->children[j]->label <<"\":";
                cin>> root->children[i]->children[j]->childCount;
                for(int k = 0; k < root->children[i]->children[j]->childCount; k++){
                    root->children[i]->children[j]->children[k] = new Node;
                    cout << "    Enter name of Subsection " << k + 1 << ": ";
                    cin.ignore();
                    getline(cin, root->children[i]->children[j]->children[k]->label);
                    root->children[i]->children[j]->children[k]->childCount = 0;

                }
            }
        }
    }

    void display() {
        if (!root) {
            cout << "No book created yet!\n";
            return;
        }
        cout << "\nBook Title: " << root->label << "\n";
        for (int i = 0; i < root->childCount; i++) {
            cout << "  Chapter " << i + 1 << ": " << root->children[i]->label << "\n";
            for (int j = 0; j < root->children[i]->childCount; j++) {
                cout << "    Section " << j + 1 << ": " << root->children[i]->children[j]->label << "\n";
                for(int k = 0; k < root->children[i]->children[j]->childCount; k++){
                    cout<<  "       Subsection " << k + 1 << ": " << root->children[i]->children[j]->children[k]->label << "\n";
                }
            }
        }
    }
};

int main() {
    BookTree bt;
    int choice;
    while (true) {
        cout << "\n1. Create Book Tree\n2. Display Book Tree\n3. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: bt.create(); break;
            case 2: bt.display(); break;
            case 3: cout << "Goodbye!\n"; return 0;
            default: cout << "Invalid choice. Try again.\n";
        }
    }
}