#include <iostream>
#include <vector>
#include <string>
using namespace std;

class TrackerMain {
public:
    int option;
    void run() {
        cout << "1. Add Income" << endl;
        cout << "2. Add Expense" << endl;
        cout << "3. View Report" << endl;
        cout << "4. Export file" << endl;
        cout << "Reset file" << endl;
        cout << "Enter a number to choose an option: ";
        cin >> option;
        while (option != 1) {
            cout << "invalid option please enter a valid option";
            cin >> option;
        }
        if (option == 1) {
            cout << "cool";
        }
    }
    void addExpense() {};
    
};


int main() { 
    cout << "Welcome to your Personal Finance Tracker" << endl;

    TrackerMain main;
    main.run();

    return 0;
}