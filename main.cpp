#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct IncomeItem {
    string category;
    float amount;
};

class TrackerAdd {
public:

    void yearName() {};

    void addMonth() {};


    void addIncome(vector<IncomeItem>& income) {
        IncomeItem item;
        cout << "type exit to end adding income" << endl;
        while (true) {
           cout << "Name of Income (salary, freelance, side gigs, bonuses, tips, rental, dividends, etc): ";
            cin >> item.category;
            if (item.category == "exit") {
                break;
            };
            cout << "Enter amount: $";
            cin >> item.amount;
        };
    };
    void addExpense() {

    };
    
};

class TrackerSettings {
    public:
        void viewReport() {

        };
        void editReport() {

        };
        void exportFile() {

        };
        void resetFile() {
            char choice;
            while (true) {
                cout << "Are you sure you want to reset your file? y/n: ";
                cin >> choice;
                if (choice == 'n' || choice == 'N') {
                    break;
                }
            }
        };

};

void showMenu(TrackerAdd& add, TrackerSettings& settings, vector<IncomeItem>& income) {
    int option;
    cout << "1. Add Income" << endl;
    cout << "2. Add Expense" << endl;
    cout << "3. View/Edit Report" << endl;
    cout << "4. Edit Report" << endl;
    cout << "5. Export file" << endl;
    cout << "6. Reset file" << endl;
    cout << "Enter a number to choose an option: ";
    cin >> option;
    while (option < 1 || option > 6) {
        cout << "Invalid option please enter a valid option: ";
        cin >> option;
    }
    if (option == 1) {
        add.addIncome(income);
    } else if (option == 2) {
        add.addExpense();
    } else if (option == 3) {
        settings.viewReport();
    } else if (option == 4) {
        settings.editReport();
    } else if (option == 5) {
        settings.exportFile();
    } else {
        settings.resetFile();
    }
}


int main() {
    vector<IncomeItem> income; 
    vector<string> month;
    
    TrackerAdd add;
    TrackerSettings settings;
    cout << "Welcome to your Personal Finance Tracker" << endl;
    showMenu(add, settings, income);

    return 0;
}