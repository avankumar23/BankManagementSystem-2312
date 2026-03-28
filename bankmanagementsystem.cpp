#include<iostream>
#include<vector>
using namespace std;

// Base class: BankAccount
class BankAccount {
protected:
    string name;
    int accountNum;
    double balance;

public:
//constructor
    BankAccount(string n, int ac, double bal) : name(n), accountNum(ac), balance(bal) {}

    virtual void deposit(double amount) {
        balance += amount;
        cout << "\t\t Successfully deposited..." << endl;
    }

    virtual void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "\t\t Successfully withdrawn..." << endl;
        } else {
            cout << "\t\t Insufficient balance..." << endl;
        }
    }

    virtual void displayAccountInfo() const {
        cout << "Name: " << name << " | Account Number: " << accountNum << " | Balance: " << balance << endl;
    }

    int getAccountNum() const {
        return accountNum;
    }

    double getBalance() const {
        return balance;
    }

    string getName() const {
        return name;
    }
};

// Derived class: CheckingAccount
class CheckingAccount : public BankAccount {
private:
    double overdraftLimit;

public:
    CheckingAccount(string n, int ac, double bal, double limit)
        : BankAccount(n, ac, bal), overdraftLimit(limit) {}

    void withdraw(double amount) override {
        if (balance + overdraftLimit >= amount) {
            balance -= amount;
            cout << "\t\t Successfully withdrawn (including overdraft)..." << endl;
        } else {
            cout << "\t\t Insufficient balance and overdraft limit exceeded..." << endl;
        }
    }

    void displayAccountInfo() const override {
        cout << "Checking Account - ";
        BankAccount::displayAccountInfo();
        cout << "Overdraft Limit: " << overdraftLimit << endl;
    }
};

// Derived class: SavingsAccount
class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(string n, int ac, double bal, double rate)
        : BankAccount(n, ac, bal), interestRate(rate) {}

    void applyInterest() {
        balance += balance * interestRate;
        cout << "\t\t Interest applied to your savings account..." << endl;
    }

    void displayAccountInfo() const override {
        cout << "Savings Account - ";
        BankAccount::displayAccountInfo();
        cout << "Interest Rate: " << interestRate * 100 << "%" << endl;
    }
};

// BankManagement class that manages multiple BankAccount objects
class BankManagement {
private:
    vector<BankAccount*> accounts;

public:
    void Addaccount(BankAccount* account) {
        accounts.push_back(account);
    }

    void showAllAccounts() {
        cout << "\t\t Show all account Holders" << endl;
        for (BankAccount* account : accounts) {
            account->displayAccountInfo();
        }
    }

    void searchAccount(int accountNum) {
        cout << "\t\t Account Holder: " << endl;
        bool found = false;
        for (BankAccount* account : accounts) {
            if (account->getAccountNum() == accountNum) {
                account->displayAccountInfo();
                found = true;
                break;
            }
        } 
        if (!found) {
            cout << "\t\t Account not found." << endl;
        }
    }

    BankAccount* findAccount(int accountNum) {
        for (BankAccount* account : accounts) {
            if (account->getAccountNum() == accountNum) {
                return account;
            }
        }
        return nullptr;
    }
};

int main() {
    int choice;
    BankManagement bank;
    char op;

    do {
        cout << "\t\t::Bank Management System" << endl;
        cout << "\t\t\t::Main Menu" << endl;
        cout << "\t\t 1. Create new account" << endl;
        cout << "\t\t 2. Show all accounts" << endl;
        cout << "\t\t 3. Search account" << endl;
        cout << "\t\t 4. Deposit" << endl;
        cout << "\t\t 5. Withdraw" << endl;
        cout << "\t\t 6. Exit" << endl;
        cout << "\t\t--------------------------------------" << endl;
        cout << "\t\t Enter the choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                int accountNum;
                double balance;
                char accountType;
                cout << "\t\t Enter Name: ";
                cin >> name;
                cout << "\t\t Enter account number: ";
                cin >> accountNum;
                cout << "\t\t Enter balance: ";
                cin >> balance;
                cout << "\t\t Enter account type (c for Checking, s for Savings): ";
                cin >> accountType;

                if (accountType == 'c' || accountType == 'C') {
                    double overdraftLimit;
                    cout << "\t\t Enter overdraft limit: ";
                    cin >> overdraftLimit;
                    CheckingAccount* newAccount = new CheckingAccount(name, accountNum, balance, overdraftLimit);
                    bank.Addaccount(newAccount);
                    cout << "\t\t Checking account created successfully..." << endl;
                }
                else if (accountType == 's' || accountType == 'S') {
                    double interestRate;
                    cout << "\t\t Enter interest rate (in decimal, e.g. 0.05 for 5%): ";
                    cin >> interestRate;
                    SavingsAccount* newAccount = new SavingsAccount(name, accountNum, balance, interestRate);
                    bank.Addaccount(newAccount);
                    cout << "\t\t Savings account created successfully..." << endl;
                }
                break;
            }
            case 2: {
                bank.showAllAccounts();
                break;
            }
            case 3: {
                int account;
                cout << "\t\t Enter account number: ";
                cin >> account;
                bank.searchAccount(account);
                break;
            }
            case 4: {
                int accountNum;
                double amount;
                cout << "\t\t Enter account number: ";
                cin >> accountNum;

                BankAccount* account = bank.findAccount(accountNum);
                if (account != nullptr) {
                    cout << "\t\t Enter the amount: ";
                    cin >> amount;
                    account->deposit(amount);
                } else {
                    cout << "\t\t Account not found." << endl;
                }
                break;
            }
            case 5: {
                int accountNum;
                double amount;
                cout << "\t\t Enter account number: ";
                cin >> accountNum;

                BankAccount* account = bank.findAccount(accountNum);
                if (account != nullptr) {
                    cout << "\t\t Enter the amount: ";
                    cin >> amount;
                    account->withdraw(amount);
                } else {
                    cout << "\t\t Account not found." << endl;
                }
                break;
            }
            case 6: {
                cout << "\t\t Exiting..." << endl;
                return 0;
            }
        }
        cout << "\t\tDo you want to continue [yes/No]? ";
        cin >> op;

    } while (op == 'y' || op == 'Y');

    return 0;
}