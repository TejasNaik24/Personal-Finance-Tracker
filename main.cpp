#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

struct IncomeItem {
    string category;
    float amount;
};

struct ExpenseItem {
    string category;
    float amount;
};

class TrackerAdd {
public:


    string addMonth() {
        string month;
        cout << "Enter the month: (January, February, etc): ";
        cin >> month;
        return month;
    };


    void addIncome(vector<IncomeItem>& income) {
        IncomeItem item;
        cout << "Type Exit To End" << endl;
        while (true) {
           cout << "Name Of Income (Salary, Freelance, Side Gigs, Bonuses, Tips, Rental, Dividends, Etc): ";
            cin >> item.category;
            if (item.category == "exit" || item.category == "Exit") {
                break;
            };
            cout << "Enter amount: $";
            cin >> item.amount;
            income.push_back(item);
            cout << "Added Sucessfully" << endl;
        };
    };
    void addExpense(vector<ExpenseItem>& expense) {
        ExpenseItem value;
        cout << "Type exit To End" << endl;
        while (true) {
        cout << "Name Of Expense (Food, Rent, Utilities, Entertainment, Transportation, Etc): ";
        cin >> value.category;
        if (value.category == "exit" || value.category == "Exit") {
            break;
        };
        cout << "Enter Amount: $";
        cin >> value.amount;
        expense.push_back(value);
        cout << "Added Sucessfully" << endl;
        };
    };
    
};

class TrackerSettings {
    public:
        void changeMonth(string& month) {
            string temp;
            cout << "Current month selected: " << month << endl;
            cout << "Type exit To Cancel" << endl;

            cout << "Enter new month: ";
            cin >> temp;

            if (temp == "exit") {
                cout << "Month change cancelled." << endl;
                return;
            }

            month = temp;
            cout << "Month changed to: " << month << endl;
            
        };
        void viewEditReport(const vector<IncomeItem>& income, const vector<ExpenseItem>& expense, const string& month, int year) {
            cout << "------" << year << " ------\n";
            cout << "\n------ Monthly Report: " << month << " ------\n";
        };
        void exportFile() {

        };
        void resetFile(vector<IncomeItem>& income, vector<ExpenseItem>& expense, string& month, int year, bool& resetFile) {
            char choice;
            cout << "Are you sure you want to reset your file? (This Will Reset Everything) y/n: ";
            cin >> choice;
            while (choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y') {
                cout << "Invalid option please enter a valid option: ";
                cin >> choice;
            }
            if (choice == 'n' || choice == 'N') {
                return;
            }
            income.clear();
            expense.clear();
            year = 0;
            month = "";
            cout << "Sucessfully Reset file" << endl;
            resetFile = true;
        }

};

void showMenu(TrackerAdd& add, TrackerSettings& settings, vector<IncomeItem>& income, vector<ExpenseItem>& expense, string& month, int year, bool& resetFile) {
    int option;
    cout << "1. Add Income" << endl;
    cout << "2. Add Expense" << endl;
    cout << "3. Change Month" << endl;
    cout << "4. View/Edit Report" << endl;
    cout << "5. Export File" << endl;
    cout << "6. Reset File" << endl;
    cout << "Enter a number to choose an option: ";
    cin >> option;
    while (option < 1 || option > 6) {
        cout << "Invalid option please enter a valid option: ";
        cin >> option;
    }
    if (option == 1) {
        add.addIncome(income);
    } else if (option == 2) {
        add.addExpense(expense);
    } else if (option == 3) {
        settings.changeMonth(month);
    } else if (option == 4) {
        settings.viewEditReport(income, expense, month, year);
    } else if (option == 5) {
        settings.exportFile();
    } else {
        settings.resetFile(income, expense, month, year, resetFile);
    }
}


int main() {
    int year;
    string month;
    vector<IncomeItem> income;
    vector<ExpenseItem> expense;
    bool resetFile = false;
    TrackerAdd add;
    TrackerSettings settings;


    cout << "Welcome to your Personal Finance Tracker" << endl;
    cout << "Enter the year: (2025, 2026, etc): ";
    cin >> year;
    month = add.addMonth();


    while (true) {
        if (resetFile) {
            cout << "Welcome to your Personal Finance Tracker" << endl;
            cout << "Enter the year: (2025, 2026, etc): ";
            cin >> year;
            month = add.addMonth();
            resetFile = false;    
        }

        showMenu(add, settings, income, expense, month, year, resetFile);
    }

    return 0;
}