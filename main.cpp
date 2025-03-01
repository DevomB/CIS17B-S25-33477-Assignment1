#include <iostream>
#include <vector>
using namespace std;

class BankAccount {
private:
    string accountHolderName;
    int accountNumber;
    double balance;
    static int accountCounter;

public:
    BankAccount(string name, double initialBalance) {
        accountHolderName = name;
        accountNumber = ++accountCounter;
        balance = (initialBalance >= 0) ? initialBalance : 0;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful! New balance: $" << balance << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful! New balance: $" << balance << endl;
        } else {
            cout << "Insufficient funds or invalid amount." << endl;
        }
    }

    double getBalance() const {
        return balance;
    }

    int getAccountNumber() const {
        return accountNumber;
    }
};

int BankAccount::accountCounter = 1000;
vector<BankAccount> accounts;

void createAccount() {
    string name;
    double initialDeposit;
    cout << "Enter account holder name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter initial deposit: ";
    cin >> initialDeposit;
    accounts.emplace_back(name, initialDeposit);
    cout << "Account created successfully! Account Number: " << accounts.back().getAccountNumber() << endl;
}

BankAccount* getAccount(int accNum) {
    for (auto &acc : accounts) {
        if (acc.getAccountNumber() == accNum)
            return &acc;
    }
    return nullptr;
}

void depositMoney() {
    int accNum;
    double amount;
    cout << "Enter account number: ";
    cin >> accNum;
    BankAccount* acc = getAccount(accNum);
    if (acc) {
        cout << "Enter amount to deposit: ";
        cin >> amount;
        acc->deposit(amount);
    } else {
        cout << "Account not found." << endl;
    }
}

void withdrawMoney() {
    int accNum;
    double amount;
    cout << "Enter account number: ";
    cin >> accNum;
    BankAccount* acc = getAccount(accNum);
    if (acc) {
        cout << "Enter amount to withdraw: ";
        cin >> amount;
        acc->withdraw(amount);
    } else {
        cout << "Account not found." << endl;
    }
}

void checkBalance() {
    int accNum;
    cout << "Enter account number: ";
    cin >> accNum;
    BankAccount* acc = getAccount(accNum);
    if (acc) {
        cout << "Current balance: $" << acc->getBalance() << endl;
    } else {
        cout << "Account not found." << endl;
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\n1. Create Account\n2. Deposit Money\n3. Withdraw Money\n4. Check Balance\n5. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5: cout << "Thank you for using Simple Bank System!" << endl; return 0;
            default: cout << "Invalid choice. Try again." << endl;
        }
    }
}
