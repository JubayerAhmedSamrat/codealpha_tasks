#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

// Generate timestamp
string currentTime() {
    time_t now = time(0);
    string dt = ctime(&now);
    dt.pop_back();
    return dt;
}

// ================= CUSTOMER =================
class Customer {
public:
    int customerID;
    string name;

    void save() {
        ofstream file("customers.txt", ios::app);
        file << customerID << " " << name << endl;
    }
};

// ================= ACCOUNT =================
class Account {
public:
    int accountNumber;
    int customerID;
    double balance;

    void save() {
        ofstream file("accounts.txt", ios::app);
        file << accountNumber << " " << customerID << " " << balance << endl;
    }
};

// ================= TRANSACTION =================
class Transaction {
public:
    int accountNumber;
    string type;
    double amount;

    void save() {
        ofstream file("transactions.txt", ios::app);
        file << accountNumber << " " << type << " " << amount << " " << currentTime() << endl;
    }
};

// ================= HELPER FUNCTIONS =================

double getBalance(int accNo) {
    ifstream file("accounts.txt");
    int a, c;
    double b;
    while(file >> a >> c >> b) {
        if(a == accNo) return b;
    }
    return -1;
}

void updateBalance(int accNo, double newBalance) {
    ifstream file("accounts.txt");
    vector<string> lines;
    int a, c;
    double b;

    while(file >> a >> c >> b) {
        if(a == accNo)
            lines.push_back(to_string(a) + " " + to_string(c) + " " + to_string(newBalance));
        else
            lines.push_back(to_string(a) + " " + to_string(c) + " " + to_string(b));
    }
    file.close();

    ofstream out("accounts.txt");
    for(auto &l : lines) out << l << endl;
}

// ================= OPERATIONS =================

void deposit(int accNo, double amt) {
    double bal = getBalance(accNo);
    if(bal < 0) { cout << "Account not found!\n"; return; }

    updateBalance(accNo, bal + amt);

    Transaction t{accNo, "Deposit", amt};
    t.save();
    cout << "Deposit successful!\n";
}

void withdraw(int accNo, double amt) {
    double bal = getBalance(accNo);
    if(bal < amt) { cout << "Insufficient balance!\n"; return; }

    updateBalance(accNo, bal - amt);

    Transaction t{accNo, "Withdraw", amt};
    t.save();
    cout << "Withdrawal successful!\n";
}

void transfer(int from, int to, double amt) {
    double balFrom = getBalance(from);
    double balTo = getBalance(to);

    if(balFrom < amt || balFrom < 0 || balTo < 0) {
        cout << "Transfer failed!\n";
        return;
    }

    updateBalance(from, balFrom - amt);
    updateBalance(to, balTo + amt);

    Transaction t1{from, "TransferOut", amt};
    Transaction t2{to, "TransferIn", amt};
    t1.save(); t2.save();

    cout << "Transfer successful!\n";
}

void showTransactions(int accNo) {
    ifstream file("transactions.txt");
    int a; string type; double amt; string time;

    cout << "\nTransactions:\n";
    while(file >> a >> type >> amt) {
        getline(file, time);
        if(a == accNo)
            cout << type << " " << amt << " " << time << endl;
    }
}

void showAccount(int accNo) {
    double bal = getBalance(accNo);
    if(bal < 0) cout << "Account not found!\n";
    else cout << "Account Balance: " << bal << endl;
}

// ================= MAIN MENU =================

int main() {
    int choice;

    while(true) {
        cout << "\n===== BANKING SYSTEM =====\n";
        cout << "1. Create Customer\n";
        cout << "2. Create Account\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Transfer\n";
        cout << "6. Show Balance\n";
        cout << "7. Show Transactions\n";
        cout << "8. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if(choice == 1) {
            Customer c;
            cout << "Customer ID: "; cin >> c.customerID;
            cout << "Name: "; cin >> c.name;
            c.save();
        }
        else if(choice == 2) {
            Account a;
            cout << "Account No: "; cin >> a.accountNumber;
            cout << "Customer ID: "; cin >> a.customerID;
            cout << "Initial Balance: "; cin >> a.balance;
            a.save();
        }
        else if(choice == 3) {
            int acc; double amt;
            cout << "Account: "; cin >> acc;
            cout << "Amount: "; cin >> amt;
            deposit(acc, amt);
        }
        else if(choice == 4) {
            int acc; double amt;
            cout << "Account: "; cin >> acc;
            cout << "Amount: "; cin >> amt;
            withdraw(acc, amt);
        }
        else if(choice == 5) {
            int from, to; double amt;
            cout << "From: "; cin >> from;
            cout << "To: "; cin >> to;
            cout << "Amount: "; cin >> amt;
            transfer(from, to, amt);
        }
        else if(choice == 6) {
            int acc; cout << "Account: "; cin >> acc;
            showAccount(acc);
        }
        else if(choice == 7) {
            int acc; cout << "Account: "; cin >> acc;
            showTransactions(acc);
        }
        else if(choice == 8) break;
    }
}

