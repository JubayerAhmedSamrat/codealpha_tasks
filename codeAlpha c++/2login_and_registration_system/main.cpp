#include <iostream>
#include <fstream>
#include <string>
#include <functional>  // for hashing

using namespace std;

// Simple hash function
string hashPassword(const string &password) {
    hash<string> hasher;
    return to_string(hasher(password));
}

// Check if username already exists
bool userExists(const string &username) {
    ifstream file("users.txt");
    string user, pass;
    while (file >> user >> pass) {
        if (user == username) return true;
    }
    return false;
}

// Registration
void registerUser() {
    string username, password;

    cout << "\n--- Registration ---\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (username.length() < 3 || password.length() < 4) {
        cout << "Username or password too short!\n";
        return;
    }

    if (userExists(username)) {
        cout << "Username already exists!\n";
        return;
    }

    ofstream file("users.txt", ios::app);
    file << username << " " << hashPassword(password) << endl;
    cout << "Registration successful!\n";
}

// Login
void loginUser() {
    string username, password;
    cout << "\n--- Login ---\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream file("users.txt");
    string user, pass;
    string hashed = hashPassword(password);

    while (file >> user >> pass) {
        if (user == username && pass == hashed) {
            cout << "Login successful! Welcome, " << username << " 🎉\n";
            return;
        }
    }

    cout << "Invalid username or password.\n";
}

int main() {
    int choice;

    while (true) {
        cout << "\n===== SYSTEM MENU =====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch(choice) {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice.\n";
        }
    }
}

