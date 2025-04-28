#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Student {
public:
    int rollNo;
    char name[30];
    char division;
    char address[50];
    void input() {
        cout << "Enter Roll Number: ";
        cin >> rollNo;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Division: ";
        cin >> division;
        cout << "Enter Address: ";
        cin >> address;
    }
    void display() {
       cout << rollNo << "\t" << name << "\t" << division << "\t" << address << endl;
    }
    int getRollNo() {
        return rollNo;
    }
};

void addStudent() {
    Student s;
    ofstream fout("students.txt", ios::app | ios::binary);
    char choice;
    if (!fout) {
        cout << "Error opening file!" << endl;
        return;
    }
    do {
        s.input();
        fout.write((char*)&s, sizeof(s));
        cout << "Add another record? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
    fout.close();
}

void showAllStudents() {
    Student s;
    ifstream fin("students.txt", ios::in | ios::binary);
    if (!fin) {
        cout << "Error opening file or file doesn't exist.\n";
        return;
    }
    cout << "\nRoll No\tName\tDivision\tAddress\n";
    while (fin.read((char*)&s, sizeof(s))) {
        s.display();
    }
    fin.close();
}

void searchStudent() {
    Student s;
    int roll, found = 0;
    fstream file("students.txt", ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }
    cout << "Enter Roll Number to search: ";
    cin >> roll;
    while (file.read((char*)&s, sizeof(s))) {
        if (s.getRollNo() == roll) {
            cout << "\nRecord Found:\n";
            s.display();
            found = 1;
            break;
        }
    }
    file.close();
    if (!found)
        cout << "Record not found.\n";
}

void deleteStudent() {
    Student s;
    int roll, found = 0;
    cout << "Enter Roll Number to delete: ";
    cin >> roll;
    ifstream fin("students.txt", ios::in | ios::binary);
    ofstream fout("temp.txt", ios::out | ios::binary);
    if (!fin || !fout) {
        cout << "Error opening files!\n";
        return;
    }
    while (fin.read((char*)&s, sizeof(s))) {
        if (s.getRollNo() != roll) {
            fout.write((char*)&s, sizeof(s));
        } else {
            found = 1;
        }
    }
    fin.close();
    fout.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    if (found)
        cout << "Record deleted successfully.\n";
    else
        cout << "Record not found.\n";
}

int main() {
    int choice;
    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Show All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1: addStudent(); break;
        case 2: showAllStudents(); break;
        case 3: searchStudent(); break;
        case 4: deleteStudent(); break;
        case 5: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);
    return 0;
}