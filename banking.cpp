#include <iostream>
#include <string>
using namespace std;

// Base class
class BankAccount {
protected:
    int accountNumber;
    string accountHolder;
    double balance;

public:
    BankAccount(int accNo, string name, double bal) {
        accountNumber = accNo;
        accountHolder = name;
        balance = bal;
    }

    virtual void deposit(double amount) {
        balance += amount;
        cout << "Deposited $" << amount << endl;
    }

    virtual void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "Withdrew $" << amount << endl;
        } else {
            cout << "Insufficient Balance!" << endl;
        }
    }

    virtual void display() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Holder Name: " << accountHolder << endl;
        cout << "Balance: $" << balance << endl;
    }

    int getAccountNumber() { return accountNumber; }
};

// Savings Account
class SavingsAccount : public BankAccount {
    double interestRate;
public:
    SavingsAccount(int accNo, string name, double bal, double rate)
        : BankAccount(accNo, name, bal), interestRate(rate) {}

    void calculateInterest() {
        double interest = balance * interestRate / 100;
        balance += interest;
        cout << "Interest $" << interest << " added" << endl;
    }

    void display() override {
        cout << endl << "--- Savings Account ---" << endl;
        BankAccount::display();
        cout << "Interest Rate: " << interestRate << "%" << endl;
    }
};

// Checking Account
class CheckingAccount : public BankAccount {
    double overdraftLimit;
public:
    CheckingAccount(int accNo, string name, double bal, double limit)
        : BankAccount(accNo, name, bal), overdraftLimit(limit) {}

    void withdraw(double amount) override {
        if (balance + overdraftLimit >= amount) {
            balance -= amount;
            cout << "Withdrew $" << amount << endl;
        } else {
            cout << "Exceeds overdraft limit!" << endl;
        }
    }

    void display() override {
        cout << endl << "--- Checking Account ---" << endl;
        BankAccount::display();
        cout << "Overdraft Limit: $" << overdraftLimit << endl;
    }
};

// Main
int main() {
    BankAccount* accounts[10];
    int accountCount = 0, choice;

    do {
        cout << endl << "=== MENU ===" << endl;
        cout << "1. Create Savings Account" << endl;
        cout << "2. Create Checking Account" << endl;
        cout << "3. Deposit" << endl;
        cout << "4. Withdraw" << endl;
        cout << "5. Display All Accounts" << endl;
        cout << "6. Calculate Interest (Savings Only)" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int accNo; string name; double bal, rate;
            cout << "Acc No: "; cin >> accNo;
            cin.ignore();
            cout << "Name: "; getline(cin, name);
            cout << "Balance: "; cin >> bal;
            cout << "Rate: "; cin >> rate;
            accounts[accountCount++] = new SavingsAccount(accNo, name, bal, rate);
        }
        else if (choice == 2) {
            int accNo; string name; double bal, limit;
            cout << "Acc No: "; cin >> accNo;
            cin.ignore();
            cout << "Name: "; getline(cin, name);
            cout << "Balance: "; cin >> bal;
            cout << "Overdraft: "; cin >> limit;
            accounts[accountCount++] = new CheckingAccount(accNo, name, bal, limit);
        }
        else if (choice == 3) {
            int accNo; double amt;
            cout << "Acc No: "; cin >> accNo;
            cout << "Deposit Amt: "; cin >> amt;
            for (int i = 0; i < accountCount; i++)
                if (accounts[i]->getAccountNumber() == accNo) accounts[i]->deposit(amt);
        }
        else if (choice == 4) {
            int accNo; double amt;
            cout << "Acc No: "; cin >> accNo;
            cout << "Withdraw Amt: "; cin >> amt;
            for (int i = 0; i < accountCount; i++)
                if (accounts[i]->getAccountNumber() == accNo) accounts[i]->withdraw(amt);
        }
        else if (choice == 5) {
            for (int i = 0; i < accountCount; i++) accounts[i]->display();
        }
        else if (choice == 6) {
            for (int i = 0; i < accountCount; i++) {
                SavingsAccount* sa = dynamic_cast<SavingsAccount*>(accounts[i]);
                if (sa) sa->calculateInterest();
            }
        }
    } while (choice != 7);

    cout << "Thank you!" << endl;
    return 0;
}
