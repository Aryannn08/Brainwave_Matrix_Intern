/*
 * ATM Interface Program
 * Created by: Aryan Chauhan
 * For: Internship/Portfolio Project
 * Description: Simulates basic ATM functions using C++
 */

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

class ATM {
private:
    long int account_No;
    string name;
    int PIN;
    double balance;
    string mobile_No;
    vector<string> transactionHistory;
    bool isLocked = false;
    int pinAttempts = 0;

public:
    void setData(long int account_No_a, string name_a, int PIN_a, double balance_a, string mobile_No_a) {
        account_No = account_No_a;
        name = name_a;
        PIN = PIN_a;
        balance = balance_a;
        mobile_No = mobile_No_a;
    }

    long int getAccountNo() { return account_No; }
    string getName() { return name; }
    int getPIN() { return PIN; }
    double getBalance() { return balance; }
    string getMobileNo() { return mobile_No; }
    vector<string> getTransactionHistory() { return transactionHistory; }
    bool getLockStatus() { return isLocked; }

    void setMobile(string mob_prev, string mob_new) {
        if (mob_prev == mobile_No) {
            mobile_No = mob_new;
            cout << endl << "Successfully Updated Mobile no.";
            cin.ignore();
            cin.get();

        } else {
            cout << endl << "Incorrect Old Mobile no!";
            cin.ignore();
            cin.get();

        }
    }

    void cashWithDraw(int amount_a) {
        if (amount_a > 0 && amount_a <= balance && amount_a <= 20000) {  // Added the withdrawal limit condition
            balance -= amount_a;
            string transaction = "Withdrew: " + to_string(amount_a);
            transactionHistory.push_back(transaction);
            cout << endl << "Please Collect Your Cash";
            cout << endl << "Available Balance: " << balance;
            cin.ignore();
            cin.get();

        } else if (amount_a > 20000) {
            cout << endl << "Withdrawal limit exceeded! You can only withdraw up to 20000.";
            cin.ignore();
            cin.get();

        } else {
            cout << endl << "Invalid Input or Insufficient Balance";
            cin.ignore();
            cin.get();

        }
    }

    void lockAccount() {
        isLocked = true;
        cout << endl << "Your account has been locked due to multiple incorrect attempts." << endl;
        cin.ignore();
        cin.get();

    }

    void trackPinAttempts() {
        pinAttempts++;
        if (pinAttempts >= 3) {
            lockAccount();
        }
    }

    void resetPinAttempts() {
        pinAttempts = 0;
    }

    void unlockAccount() {
        isLocked = false;
        pinAttempts = 0;
        cout << endl << "Your account has been unlocked. Please try again with correct details.";
        cin.ignore();
        cin.get();

    }

    void setPIN(int newPIN) {
    PIN = newPIN;
    }

};

int main() {
    int choice = 0, enterPIN;
    long int enterAccountNo;

    system("clear");

    ATM user1;
    user1.setData(9700165234, "Aryan", 1234, 50000, "6396342014");

    do {
        system("clear");

        cout << endl << "****Welcome to ATM*****" << endl;
        cout << endl << "Enter Your Account No: ";
        cin >> enterAccountNo;

        cout << endl << "Enter PIN: ";
        cin >> enterPIN;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');


        if ((enterAccountNo == user1.getAccountNo()) && (enterPIN == user1.getPIN())) {
            user1.resetPinAttempts();

            do {
                int amount = 0;
                string oldMobileNo, newMobileNo;

                if (user1.getLockStatus()) {
                    cout << "Account is locked. Please contact support." << endl;
                    break;
                }

                system("clear");

                cout << endl << "**** Welcome to ATM *****" << endl;
                cout << endl << "Select an option: ";
                cout << endl << "1. Check Balance";
                cout << endl << "2. Cash Withdraw";
                cout << endl << "3. Show User Details";
                cout << endl << "4. Update Mobile No.";
                cout << endl << "5. View Transaction History";
                cout << endl << "6. Lock Account (for security purposes)";
                cout << endl << "7. Change PIN";
                cout << endl << "8. Exit" <<endl;
                cin >> choice;

                switch (choice) {
                    case 1:
                        cout << endl << "Your Bank balance is: " << user1.getBalance();
                        cin.ignore();
                        cin.get();

                        break;

                    case 2:
                        cout << endl << "Enter the amount: ";
                        cin >> amount;
                        user1.cashWithDraw(amount);
                        break;

                    case 3:
                        cout << endl << "*** User Details are: ***";
                        cout << endl << "-> Account No: " << user1.getAccountNo();
                        cout << endl << "-> Name: " << user1.getName();
                        cout << endl << "-> Balance: " << user1.getBalance();
                        cout << endl << "-> Mobile No.: " << user1.getMobileNo();
                        cin.ignore();
                        cin.get();
                        break;

                    case 4:
                        cout << endl << "Enter Old Mobile No.: ";
                        cin >> oldMobileNo;
                        cout << endl << "Enter New Mobile No.: ";
                        cin >> newMobileNo;
                        user1.setMobile(oldMobileNo, newMobileNo);
                        break;

                    case 5:
                        {
                            vector<string> transactions = user1.getTransactionHistory();
                            cout << endl << "*** Transaction History ***";
                            for (const string& transaction : transactions) {
                                cout << endl << transaction;
                            }
                            cin.ignore();
                            cin.get();
                        }
                        break;

                    case 6:
                        user1.lockAccount();
                        break;

                    case 7:
                        {
                            int oldPIN, newPIN;
                            cout << endl << "Enter Old PIN: ";
                            cin >> oldPIN;
                            cout << "Enter New PIN: ";
                            cin >> newPIN;

                            if (oldPIN == user1.getPIN()) {
                                user1.setPIN(newPIN);
                                cout << endl << "PIN changed successfully.";
                            } else {
                                cout << endl << "Incorrect old PIN.";
                            }
                            cin.ignore();
                            cin.get();
                            break;
                        }

                    case 8: 
                        exit(0);


                    default:
                        cout << endl << "Enter Valid Data !!!";
                        break;
                }

            } while (true);

        } else {
            cout << endl << "User Details are Invalid !!! ";
            user1.trackPinAttempts();

            if (user1.getLockStatus()) {
                char retryChoice;
                cout << endl << "Would you like to try again? (y/n): ";
                cin >> retryChoice;

                if (retryChoice == 'y' || retryChoice == 'Y') {
                    cout << "Please wait for 30 seconds before retrying..." << endl;

                    // Wait for 30 seconds (using sleep function for Linux)
                    sleep(30);  // Use Sleep(30000) on Windows instead
                    user1.unlockAccount();
                    continue;  // Restart the loop for a new login attempt
                } else {
                    cout << "Exiting. Please try again later.";
                    break;  // Exit the program
                }
            }
            cin.ignore();
            cin.get();

        }

    } while (true);

    return 0;
}