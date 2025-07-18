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
        cout << "5. Reset file" << endl;
        cout << "Enter a number to choose an option: ";
        cin >> option;
        while (option < 1 || option > 5) {
            cout << "invalid option please enter a valid option ";
            cin >> option;
        }
        if (option == 1) {
            addIncome();
        } else if (option == 2) {
            addExpense();
        } else if (option == 3) {
            viewReport();
        } else if (option == 4) {
            exportFile();
        } else {
            restFile();
        }
    }
    void addIncome() {

    };
    void addExpense() {

    };
    void viewReport() {

    }
    void exportFile() {

    };
    void restFile() {

    };
    
};


int main() { 
    cout << "Welcome to your Personal Finance Tracker" << endl;

    TrackerMain main;
    main.run();

    return 0;
}