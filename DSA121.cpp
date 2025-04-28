#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Employee {
    int id;
    char name[50];
    char designation[50];
    float salary;
};

void addEmployee() {
    Employee emp;
    ofstream fout("employee_data.dat", ios::binary | ios::app);
    cout << "Enter ID: ";
    cin >> emp.id;
    cin.ignore();
    cout << "Enter Name: ";
    cin.getline(emp.name, 50);
    cout << "Enter Designation: ";
    cin.getline(emp.designation, 50);
    cout << "Enter Salary: ";
    cin >> emp.salary;
    fout.write((char*)&emp, sizeof(emp));
    fout.close();
    cout << "Employee added successfully!\n";
}

void displayEmployee() {
    Employee emp;
    int searchID;
    bool found = false;
    ifstream fin("employee_data.dat", ios::binary);
    cout << "Enter ID to search: "; 
    cin >> searchID;
    while (fin.read((char*)&emp, sizeof(emp))) {
        if (emp.id == searchID) {
            cout << "\n--- Employee Found ---\n";
            cout << "ID: " << emp.id << "\nName: " << emp.name
                 << "\nDesignation: " << emp.designation
                 << "\nSalary: " << emp.salary << endl;
            found = true;
            break;
        }
    }
    if (!found)
        cout << "Employee not found!\n";
    fin.close();
}

void deleteEmployee() {
    Employee emp;
    int delID;
    bool found = false;
    cout << "Enter ID to delete: ";
    cin >> delID;
    ifstream fin("employee_data.dat", ios::binary);
    ofstream fout("temp.dat", ios::binary);
    while (fin.read((char*)&emp, sizeof(emp))) {
        if (emp.id != delID) {
            fout.write((char*)&emp, sizeof(emp));
        } else {
            found = true;
        }
    }
    fin.close();
    fout.close();
    remove("employee_data.dat");
    rename("temp.dat", "employee_data.dat");
    if (found)
        cout << "Employee deleted successfully!\n";
    else
        cout << "Employee not found!\n";
}

int main() {
    int choice;
    do {
        cout << "\n--- Employee Management System ---\n";
        cout << "1. Add Employee\n";
        cout << "2. Display Employee\n";
        cout << "3. Delete Employee\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployee(); break;
            case 3: deleteEmployee(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
    return 0;
}