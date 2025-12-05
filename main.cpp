#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Student {
    string roll;
    string name;
    float marks;
};

string currentUser, currentRole;

// ---------------- LOGIN SYSTEM -----------------

bool login() {
    string u, p, r;
    string inUser, inPass;

    cout << "USERNAME: ";
    cin >> inUser;
    cout << "PASSWORD: ";
    cin >> inPass;

    ifstream fin("credentials.txt");
    if (!fin) {
        cout << "No credentials file found!\n";
        return false;
    }

    while (fin >> u >> p >> r) {
        if (u == inUser && p == inPass) {
            currentUser = u;
            currentRole = r;
            return true;
        }
    }
    return false;
}

// --------- READ ALL STUDENTS FROM FILE ------------

vector<Student> loadStudents() {
    vector<Student> list;
    ifstream fin("students.txt");
    Student s;

    while (fin >> s.roll >> s.name >> s.marks) {
        list.push_back(s);
    }
    return list;
}

// --------- SAVE ALL STUDENTS TO FILE ------------

void saveStudents(const vector<Student> &list) {
    ofstream fout("students.txt");
    for (auto &s : list) {
        fout << s.roll << " " << s.name << " " << s.marks << "\n";
    }
}

// ---------------- ADD STUDENT -----------------

void addStudent() {
    Student s;
    cout << "Enter Roll Number: ";
    cin >> s.roll;
    cout << "Enter Name: ";
    cin >> s.name;
    cout << "Enter Marks: ";
    cin >> s.marks;

    ofstream fout("students.txt", ios::app);
    fout << s.roll << " " << s.name << " " << s.marks << "\n";

    cout << "Student Added Successfully!\n";
}

// ---------------- DISPLAY STUDENTS -----------------

void displayStudents() {
    vector<Student> list = loadStudents();

    cout << "\nROLL\tNAME\tMARKS\n";
    for (auto &s : list) {
        cout << s.roll << "\t" << s.name << "\t" << s.marks << "\n";
    }
}

// ---------------- SEARCH STUDENT ------------------

void searchStudent() {
    string r;
    cout << "Enter Roll to Search: ";
    cin >> r;

    vector<Student> list = loadStudents();
    for (auto &s : list) {
        if (s.roll == r) {
            cout << "Found → " << s.roll << " " << s.name << " " << s.marks << "\n";
            return;
        }
    }
    cout << "Student Not Found!\n";
}

// ---------------- DELETE STUDENT ------------------

void deleteStudent() {
    string r;
    cout << "Enter Roll to Delete: ";
    cin >> r;

    vector<Student> list = loadStudents();
    vector<Student> newList;

    bool found = false;
    for (auto &s : list) {
        if (s.roll != r) newList.push_back(s);
        else found = true;
    }

    saveStudents(newList);

    if (found) cout << "Deleted Successfully!\n";
    else cout << "Roll Not Found!\n";
}

// ---------------- UPDATE STUDENT ------------------

void updateStudent() {
    string r;
    cout << "Enter Roll to Update: ";
    cin >> r;

    vector<Student> list = loadStudents();
    bool found = false;

    for (auto &s : list) {
        if (s.roll == r) {
            found = true;
            cout << "New Name: ";
            cin >> s.name;
            cout << "New Marks: ";
            cin >> s.marks;
        }
    }

    saveStudents(list);

    if (found) cout << "Updated Successfully!\n";
    else cout << "Roll Not Found!\n";
}

// ---------------- SORTING STUDENTS ------------------

void sortStudents() {
    vector<Student> list = loadStudents();

    int choice;
    cout << "\nSort by Marks:\n1. Ascending\n2. Descending\nChoice: ";
    cin >> choice;

    if (choice == 1)
        sort(list.begin(), list.end(), [](Student &a, Student &b){ return a.marks < b.marks; });
    else
        sort(list.begin(), list.end(), [](Student &a, Student &b){ return a.marks > b.marks; });

    cout << "\nSorted Students:\n";
    cout << "ROLL\tNAME\tMARKS\n";
    for (auto &s : list) {
        cout << s.roll << "\t" << s.name << "\t" << s.marks << "\n";
    }
}

// ---------------- MENU FUNCTIONS -----------------

void adminMenu() {
    int c;
    while (true) {
        cout << "\nADMIN MENU\n1.Add\n2.Display\n3.Search\n4.Update\n5.Delete\n6.Sort by Marks\n7.Logout\nChoice: ";
        cin >> c;

        if (c == 1) addStudent();
        else if (c == 2) displayStudents();
        else if (c == 3) searchStudent();
        else if (c == 4) updateStudent();
        else if (c == 5) deleteStudent();
        else if (c == 6) sortStudents();
        else return;
    }
}

void staffMenu() {
    int c;
    while (true) {
        cout << "\nSTAFF MENU\n1.Add\n2.Display\n3.Search\n4.Update\n5.Sort by Marks\n6.Logout\nChoice: ";
        cin >> c;

        if (c == 1) addStudent();
        else if (c == 2) displayStudents();
        else if (c == 3) searchStudent();
        else if (c == 4) updateStudent();
        else if (c == 5) sortStudents();
        else return;
    }
}

void guestMenu() {
    int c;
    while (true) {
        cout << "\nGUEST MENU\n1.Display\n2.Search\n3.Sort by Marks\n4.Logout\nChoice: ";
        cin >> c;

        if (c == 1) displayStudents();
        else if (c == 2) searchStudent();
        else if (c == 3) sortStudents();
        else return;
    }
}

// ---------------- MAIN -----------------

int main() {
    if (!login()) {
        cout << "Invalid Login!\n";
        return 0;
    }

    cout << "Logged in as: " << currentRole << "\n";

    if (currentRole == "admin") adminMenu();
    else if (currentRole == "staff") staffMenu();
    else guestMenu();

    return 0;
}