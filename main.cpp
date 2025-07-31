#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
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


    void addMonth(vector<string>& months) {
        string month;
        cout << "Enter the month: (January, February, etc): ";
        cin >> month;
        months.push_back(month);
    };


    void addIncome(vector<IncomeItem>& income, vector<string>& months) {
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
    void addExpense(vector<ExpenseItem>& expense, vector<string>& months) {
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
        void addEditFile(TrackerAdd& add, vector<string>& months, string& currentMonth, int& year) {
            while (true) {
                int decision;
                cout << "1. Edit Year" << endl;
                cout << "2. Edit Month" << endl;
                cout << "3. Back" << endl;
                cout << "Enter a number to choose an option: ";
                cin >> decision;
                while (decision < 1 || decision > 3) {
                    cout << "Invalid option please enter a valid option: ";
                    cin >> decision;
                }
                if (decision == 1) {
                    changeYear(year);
                } else  if (decision == 2){
                    monthMenu(add, months, currentMonth);
                } else {
                    break;
                }
            }

        }

        void monthMenu(TrackerAdd& add, vector<string>& months, string& currentMonth) {
            int alternative;
            cout << "1. Add Month" << endl;
            cout << "2. Remove Month" << endl;
            cout << "3. Edit Month Name" << endl;
            cout << "4. Add To Month" << endl;
            cout << "Enter a number to choose an option: ";
            cin >> alternative;
            while (alternative < 1 || alternative > 4) {
                cout << "Invalid option please enter a valid option: ";
                cin >> alternative;
            }

            switch (alternative) {
                case 1:
                    add.addMonth(months);
                    break;
                case 2:
                    removeMonth(months);
                    break;
                case 3:
                    break;
                case 4:
                    selectMonth(currentMonth, months);
                    break;

            }
        }
        void changeYear(int& year) {
            string currentTemp;
            cout << "Current Year: " << year << endl;
            cout << "Type exit To Cancel" << endl;

            cout << "Enter new year: ";
            cin >> currentTemp;
            if (currentTemp == "exit") {
                cout << "Year Change Cancelled" << endl;
                return;
            }
            while (true) {
                try {
                    year = stoi(currentTemp);
                    cout << "Year changed to: " << year << endl;
                    break;
                } catch (invalid_argument&) {
                    cout << "Invalid input. Please enter a valid year: ";
                    cin >> currentTemp;

                    if (currentTemp == "exit") {
                        cout << "Year Change Cancelled" << endl;
                        return;
                    }
                }
            }

        }

        void removeMonth(vector<string>& months) {
            if (months.empty()) {
                cout << "No Months Have Been Added" << endl;
                return;
            }
            int type;
            cout << "Choose which month to remove" << endl;
            for (int i = 0; i < months.size(); ++i) {
                cout << i + 1 << ". " << months[i] << endl;
            }
            cout << "Enter a number to choose an option: ";
            cin >> type;
            while (true) {
                if (type >= 1 && type <= months.size()) {
                    string removedMonth = months[type - 1];
                    months.erase(months.begin() + (type - 1));
                    cout << "Removed month: " << removedMonth << endl;
                    break;
                } else {
                    cout << "Invalid option please enter a valid option: ";
                    cin >> type;
                }
            }
        }
        void changeMonth() {
            string temp;
            cout << "Current month selected: " << "month" << endl;
            cout << "Type exit To Cancel" << endl;

            cout << "Enter new month: ";
            cin >> temp;

            if (temp == "exit") {
                cout << "Month change cancelled." << endl;
                return;
            }

            cout << "Month changed to: " << "month" << endl;
            
        };
        void selectMonth(string currentMonth, vector<string>& months) {
            if (months.empty()) {
                cout << "Please Enter A Month To Edit" << endl;
                return;
            }
            int selection;
            cout << "Available months: " << endl;
            for (int i = 0; i < months.size(); ++i) {
                cout << i + 1 << ". " << months[i] << endl;
            }
            while (true) {
                cout << "Enter a number to choose an option: ";
                cin >> selection;
                
                if (selection >= 1 && selection <= months.size()) {
                    currentMonth = months[selection - 1];
                    break;
                } else {
                    cout << "Invalid selection. Please try again." << endl;
                }
            }
            currentMonth = selection;
            cout << "Currently Editing: " << currentMonth << endl;

        };
        void viewReport(const vector<IncomeItem>& income, const vector<ExpenseItem>& expense, vector<string> months, int year) {
            cout << "|" << "----------------------------------------------------------------------------------------------------------------------------------------------------------" << "|" << endl;
            cout << "|" << right << setw(78) << year << setw(77) << "|" << endl;
            cout << "|" << "----------------------------------------------------------------------------------------------------------------------------------------------------------" << "|" << endl;
            cout << "|" << " Category " << "|";
            for (string month : months) {
                cout << "  " << month << "  " << "|";
            }
            cout << right << setw(6) << "total" << setw(4) << "|" << endl;
            cout << "|" << "----------------------------------------------------------------------------------------------------------------------------------------------------------"<< "|" << endl;
            cout << "|" << "  Income  " << "|" << right << setw(144) << "|" << endl;
            cout << "|" << "----------------------------------------------------------------------------------------------------------------------------------------------------------"<< "|" << endl;


        };
        void exportFile() {

        };
        void resetFile(vector<IncomeItem>& income, vector<ExpenseItem>& expense, vector<string> months, int year, bool& resetFile) {
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
            months.clear();
            year = 0;
            cout << "Sucessfully Reset file" << endl;
            resetFile = true;
        }

};

void showMenu(TrackerAdd& add, TrackerSettings& settings, vector<IncomeItem>& income, vector<ExpenseItem>& expense, string currentMonth, vector<string>& months, int& year, bool& resetFile) {
    int intOption;
    string strOption;
    cout << "1. Add/Edit File" << endl;
    cout << "2. View Report" << endl;
    cout << "3. Export File" << endl;
    cout << "4. Reset File" << endl;
    cout << "Enter a number to choose an option: ";
    cin >> strOption;
    while (true) {
        try {
            intOption = stoi(strOption);
            break;
        } catch (invalid_argument&) {
            cout << "Invalid option please enter a valid option: ";
            cin >> strOption;
        }
    }
    while (intOption < 1 || intOption > 4) {
        cout << "Invalid option please enter a valid option: ";
        cin >> intOption;
    }
    if (intOption == 1) {
        settings.addEditFile(add, months, currentMonth, year);
    } else if (intOption == 2) {
        settings.viewReport(income, expense, months, year);
    } else if (intOption == 3) {
        cout << "placeholder";
    } else {
        settings.resetFile(income, expense, months, year, resetFile);
    }
}


int main() {
    int year;
    string currentMonth;
    vector<IncomeItem> income;
    vector<ExpenseItem> expense;
    vector<string> months;
    bool resetFile = false;
    TrackerAdd add;
    TrackerSettings settings;


    cout << "Welcome to your Personal Finance Tracker" << endl;
    cout << "Enter the year: (2025, 2026, etc): ";
    cin >> year;

    while (true) {
        if (resetFile) {
            cout << "Welcome to your Personal Finance Tracker" << endl;
            cout << "Enter the year: (2025, 2026, etc): ";
            cin >> year;
            resetFile = false;    
        }

        showMenu(add, settings, income, expense, currentMonth, months, year, resetFile);
    }

    return 0;
}