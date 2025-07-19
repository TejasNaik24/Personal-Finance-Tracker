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
    void addIncome(vector<IncomeItem>& income) {
        IncomeItem item;
        cout << "Name of Income (salary,)";
        item.category = "what";
        item.amount = 2.2;
        cout << item.category;
        cout << item.amount;
    };
    void addExpense() {

    };
    
};

class TrackerSettings {
    public:
        void viewReport() {

        }
        void exportFile() {

        };
        void resetFile() {
            
        };

};

void showMenu(TrackerAdd& add, TrackerSettings& settings, vector<IncomeItem>& income) {
    int option;
    cout << "1. Add Income" << endl;
    cout << "2. Add Expense" << endl;
    cout << "3. View Report" << endl;
    cout << "4. Export file" << endl;
    cout << "5. Reset file" << endl;
    cout << "Enter a number to choose an option: ";
    cin >> option;
    while (option < 1 || option > 5) {
        cout << "Invalid option please enter a valid option ";
        cin >> option;
    }
    if (option == 1) {
        add.addIncome(income);
    } else if (option == 2) {
        add.addExpense();
    } else if (option == 3) {
        settings.viewReport();
    } else if (option == 4) {
        settings.exportFile();
    } else {
        settings.resetFile();
    }
}


int main() {
    vector<IncomeItem> income; 
    
    TrackerAdd add;
    TrackerSettings settings;
    cout << "Welcome to your Personal Finance Tracker" << endl;
    showMenu(add, settings, income);

    return 0;
}