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

    // Deposit and Withdraw functions -- Error handling included

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount. It must be greater than zero." << endl;
            return;
        }
        balance += amount;
        cout << "Deposit successful! New balance: $" << balance << endl;
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount. It must be greater than zero." << endl;
            return;
        }
        if (amount > balance) {
            cout << "Insufficient funds." << endl;
            return;
        }
        balance -= amount;
        cout << "Withdrawal successful! New balance: $" << balance << endl;
    }

    // Getters

    // The const at the end of the function declaration => Will not modify data

    double getBalance() const {
        return balance;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    string getAccountHolderName() const {
        return accountHolderName;
    }
};



int BankAccount::accountCounter = 1000; // Account numbers start @ 1000
vector<BankAccount> accounts; // Vector to store all accounts as vectors can grow dynamically

// Static functions -- Not inside the class to keep it clutter-free 

void createAccount() {
    string name;
    double initialDeposit;
    
    cout << "Enter account holder name: ";
    cin.ignore();
    getline(cin, name);
    
    while (true) {
        cout << "Enter initial deposit: ";
        cin >> initialDeposit;
        if (cin.fail() || initialDeposit < 0) {
            cout << "Invalid deposit. Please enter a valid positive amount." << endl;
            cin.clear();  // Clear error flag
            cin.ignore(10000, '\n');  // Ignore invalid input
        } else {
            break;
        }
    }

    accounts.emplace_back(name, initialDeposit); // Add account to the vector
    cout << "Account created successfully! Account Number: " << accounts.back().getAccountNumber() << endl;
}

// Get account function returning a pointer to the account

BankAccount* getAccount(int accNum) {
    for (auto &acc : accounts) {
        if (acc.getAccountNumber() == accNum)
            return &acc;
    }
    return nullptr;
}

// Deposit money function using a pointer to the account

void depositMoney(BankAccount* acc) {
    double amount;
    
    while (true) {
        cout << "Enter amount to deposit: ";
        cin >> amount;
        if (cin.fail() || amount <= 0) {
            cout << "Invalid amount. Please enter a positive number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        } else {
            break;
        }
    }

    acc->deposit(amount);
}

// Withdraw money function using a pointer to the account

void withdrawMoney(BankAccount* acc) {
    double amount;
    
    while (true) {
        cout << "Enter amount to withdraw: ";
        cin >> amount;
        if (cin.fail() || amount <= 0) {
            cout << "Invalid amount. Please enter a positive number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        } else if (amount > acc->getBalance()) {
            cout << "Insufficient funds." << endl;
            break;
        } else {
            break;
        }
    }

    if (amount <= acc->getBalance()) {
        acc->withdraw(amount);
    }
}

// Check balance function

void checkBalance(BankAccount* acc) {
    cout << "Current balance: $" << acc->getBalance() << endl;
}


// Switch account function using a pointer to a pointer

void switchAccount(BankAccount*& currentAccount) {
    int accNum;
    cout << "Enter account number to switch to: ";
    cin >> accNum;
    
    BankAccount* acc = getAccount(accNum);
    if (acc) {
        currentAccount = acc;
        cout << "Switched to account: " << acc->getAccountHolderName() << " (Account Number: " << acc->getAccountNumber() << ")" << endl;
    } else {
        cout << "Account not found." << endl;
    }
}

int main() {
    int choice;
    BankAccount* currentAccount = nullptr;

    // This makes this loop continuous until user exits

    while (true) {
        cout << "\n1. Create Account\n2. Deposit Money\n3. Withdraw Money\n4. Check Balance\n5. Switch Account\n6. Exit\nEnter your choice: ";
        cin >> choice;

        // Input error handling with the ignore function
        if (cin.fail()) {
            cout << "Invalid input. Please enter a valid choice." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        

        /*
            This is a big switch statement which is regulating different things from being executed
            based on the choice of the user.
        */
        switch (choice) {
            case 1: 

                createAccount();
                break;

            case 2:

                if (currentAccount) {
                    depositMoney(currentAccount);
                } else {
                    cout << "No account selected. Please switch to an account first." << endl;
                }
                break;

            case 3:

                if (currentAccount) {
                    withdrawMoney(currentAccount);
                } else {
                    cout << "No account selected. Please switch to an account first." << endl;
                }
                break;

            case 4:

                if (currentAccount) {
                    checkBalance(currentAccount);
                } else {
                    cout << "No account selected. Please switch to an account first." << endl;
                }
                break;

            case 5:

                switchAccount(currentAccount);
                break;

            case 6:

                cout << "Thank you for using Simple Bank System!" << endl;
                return 0;

            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}
