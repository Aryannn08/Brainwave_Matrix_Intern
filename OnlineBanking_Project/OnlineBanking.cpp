#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Account {
    int accountNumber;
    string name;
    double balance;
};

vector<Account> accounts;
int nextAccountNumber = 1001;

// Function to find an account by number
Account* findAccount(int accNum) {
    for (auto& acc : accounts) {
        if (acc.accountNumber == accNum)
            return &acc;
    }
    return nullptr;
}

void createAccount() {
    Account newAcc;
    newAcc.accountNumber = nextAccountNumber++;
    cout << "Enter account holder name: ";
    cin.ignore();
    getline(cin, newAcc.name);
    newAcc.balance = 0.0;
    accounts.push_back(newAcc);
    cout << "Account created successfully!\n";
    cout << "Account Number: " << newAcc.accountNumber << "\n";
}

void deposit() {
    int accNum;
    double amount;
    cout << "Enter account number: ";
    cin >> accNum;

    Account* acc = findAccount(accNum);
    if (acc) {
        cout << "Enter amount to deposit: ";
        cin >> amount;
        if (amount > 0) {
            acc->balance += amount;
            cout << "Deposit successful. New Balance: ₹" << acc->balance << "\n";
        } else {
            cout << "Invalid amount.\n";
        }
    } else {
        cout << "Account not found.\n";
    }
}

void withdraw() {
    int accNum;
    double amount;
    cout << "Enter account number: ";
    cin >> accNum;

    Account* acc = findAccount(accNum);
    if (acc) {
        cout << "Enter amount to withdraw: ";
        cin >> amount;
        if (amount > 0 && amount <= acc->balance) {
            acc->balance -= amount;
            cout << "Withdrawal successful. Remaining Balance: ₹" << acc->balance << "\n";
        } else {
            cout << "Insufficient balance or invalid amount.\n";
        }
    } else {
        cout << "Account not found.\n";
    }
}

void transfer() {
    int fromAccNum, toAccNum;
    double amount;
    cout << "Enter sender account number: ";
    cin >> fromAccNum;
    cout << "Enter receiver account number: ";
    cin >> toAccNum;

    Account* sender = findAccount(fromAccNum);
    Account* receiver = findAccount(toAccNum);

    if (sender && receiver) {
        cout << "Enter amount to transfer: ";
        cin >> amount;
        if (amount > 0 && amount <= sender->balance) {
            sender->balance -= amount;
            receiver->balance += amount;
            cout << "Transfer successful.\n";
            cout << "Sender New Balance: ₹" << sender->balance << "\n";
        } else {
            cout << "Invalid amount or insufficient funds.\n";
        }
    } else {
        cout << "One or both accounts not found.\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\n====== Online Banking System ======\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Funds\n";
        cout << "3. Withdraw Funds\n";
        cout << "4. Transfer Money\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: transfer(); break;
            case 5: cout << "Thank you for using our banking system!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
