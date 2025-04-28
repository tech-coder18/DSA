#include<iostream>
using namespace std;

class Node {
public:
    string key, meaning;
    Node *left, *right;
    Node(string k, string m) : key(k), meaning(m), left(NULL), right(NULL) {}
};

class AVL {
    Node *root;
public:
    AVL() { root = NULL; }

    int height(Node* n) {
        return n ? 1 + max(height(n->left), height(n->right)) : -1;
    }

    int balanceFactor(Node* n) {
        return height(n->left) - height(n->right);
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        return x;
    }

    Node* balance(Node* n) {
        int bf = balanceFactor(n);
        if (bf > 1) {
            if (balanceFactor(n->left) < 0) n->left = rotateLeft(n->left);
            return rotateRight(n);
        }
        if (bf < -1) {
            if (balanceFactor(n->right) > 0) n->right = rotateRight(n->right);
            return rotateLeft(n);
        }
        return n;
    }

    Node* insert(Node* n, string k, string m) {
        if (!n) return new Node(k, m);
        if (k < n->key) n->left = insert(n->left, k, m);
        else if (k > n->key) n->right = insert(n->right, k, m);
        else n->meaning = m; // update meaning if key exists
        return balance(n);
    }

    Node* findMin(Node* n) {
        return n->left ? findMin(n->left) : n;
    }

    Node* deleteNode(Node* n, string k) {
        if (!n) return NULL;
        if (k < n->key) n->left = deleteNode(n->left, k);
        else if (k > n->key) n->right = deleteNode(n->right, k);
        else {
            if (!n->left || !n->right) {
                Node* temp = n->left ? n->left : n->right;
                delete n;
                return temp;
            } else {
                Node* minNode = findMin(n->right);
                n->key = minNode->key;
                n->meaning = minNode->meaning;
                n->right = deleteNode(n->right, minNode->key);
            }
        }
        return balance(n);
    }

    bool search(Node* n, string k) {
        if (!n) return false;
        if (k == n->key) return true;
        if (k < n->key) return search(n->left, k);
        else return search(n->right, k);
    }

    void inorder(Node* n) {
        if (n) {
            inorder(n->left);
            cout << n->key << " : " << n->meaning << endl;
            inorder(n->right);
        }
    }

    void reverseInorder(Node* n) {
        if (n) {
            reverseInorder(n->right);
            cout << n->key << " : " << n->meaning << endl;
            reverseInorder(n->left);
        }
    }

    // public functions
    void add() {
        string k, m;
        cout << "Enter keyword: "; cin >> k;
        cout << "Enter meaning: "; cin >> m;
        root = insert(root, k, m);
    }

    void remove() {
        string k;
        cout << "Enter keyword to delete: "; cin >> k;
        root = deleteNode(root, k);
    }

    void searchKey() {
        string k;
        cout << "Enter keyword to search: "; cin >> k;
        cout << (search(root, k) ? "Found" : "Not Found") << endl;
    }

    void displayAsc() {
        cout << "Dictionary in Ascending Order:\n";
        inorder(root);
    }

    void displayDesc() {
        cout << "Dictionary in Descending Order:\n";
        reverseInorder(root);
    }

    int maxComparisons() {
        return height(root) + 1;
    }
};

int main() {
    AVL tree;
    int choice;
    char cont;
    do {
        cout << "\n1. Add\n2. Delete\n3. Search\n4. Display Ascending\n5. Display Descending\n6. Max Comparisons\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: tree.add(); break;
            case 2: tree.remove(); break;
            case 3: tree.searchKey(); break;
            case 4: tree.displayAsc(); break;
            case 5: tree.displayDesc(); break;
            case 6: cout << "Max Comparisons = " << tree.maxComparisons() << endl; break;
            default: cout << "Invalid Choice!\n";
        }
        cout << "Continue? (y/n): ";
        cin >> cont;
    } while (cont == 'y' || cont == 'Y');
    return 0;
}