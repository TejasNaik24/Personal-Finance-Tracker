#include <iostream>
#include <vector>
#include <map>
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

class TrackerModify {
public:
    void addMonth(vector<string>& months) {
        string month;
        cout << "Enter the month: (January, February, etc): ";
        cin >> month;
        months.push_back(month);
    };
    void addIncome(map<string, vector<IncomeItem>>& incomeByMonth, const string& currentMonth) {
        IncomeItem item;
        string strAmount;
        cout << "Type Exit To End" << endl;
        while (true) {
           cout << "Name Of Income (Salary, Freelance, Side Gigs, Bonuses, Tips, Rental, Dividends, Etc): ";
            cin >> item.category;
            if (item.category == "exit" || item.category == "Exit") {
                break;
            };
            cout << "Enter amount: $";
            while (true) {
                cin >> strAmount;
                try {
                    item.amount = stoi(strAmount);
                    incomeByMonth[currentMonth].push_back(item);
                    cout << "Added Sucessfully" << endl;
                    break;
                } catch (invalid_argument&) {
                     cout << "Invalid Number. Please Try Again: $";
                }
            }
        };
    };
    void removeIncome(const string& currentMonth, map<string, vector<IncomeItem>>& incomeByMonth) {
        if (incomeByMonth.find(currentMonth) == incomeByMonth.end() || incomeByMonth[currentMonth].empty()) {
            cout << "No income items for " << currentMonth << " to remove." << endl;
            return;
        }

        vector<IncomeItem>& incomes = incomeByMonth[currentMonth];

        cout << "Income items for " << currentMonth << ":\n";
        for (size_t i = 0; i < incomes.size(); ++i) {
            cout << i + 1 << ". " << incomes[i].category << " $" << incomes[i].amount << endl;
        }

        int intRemoveIncome;
        string strRemoveIncome;

        cout << "Type exit To Cancel" << endl;
        cout << "Enter a number to choose an option: ";
        while (true) {
            cin >> strRemoveIncome;
            if (strRemoveIncome == "exit") {
                return;
            }
            try {
                intRemoveIncome = stoi(strRemoveIncome);
                if (intRemoveIncome < 1 || intRemoveIncome > incomes.size()) {
                    cout << "Invalid selection. Please try again: ";
                } else {
                    IncomeItem removedItem = incomes[intRemoveIncome - 1];
                    incomes.erase(incomes.begin() + (intRemoveIncome - 1));
                    cout << "Removed income: " << removedItem.category << "$" << removedItem.amount << endl;
                    break;
                }
            } catch (invalid_argument&) {
                cout << "Invalid option please enter a valid option: ";
            }
        }
    }
    void editIncome(map<string, vector<IncomeItem>>& incomeByMonth, const string& currentMonth) {
        string newName, newAmountStr, input;
        float newAmount;
        int choice;
        vector<IncomeItem>& incomes = incomeByMonth[currentMonth];

        if (incomes.empty()) {
            cout << "No income entries to edit for " << currentMonth << "." << endl;
            return;
        }
        cout << "Income entries for " << currentMonth << ":" << endl;

        for (int i = 0; i < incomes.size(); ++i) {
            cout << i + 1 << ". " << incomes[i].category << " $" << incomes[i].amount << endl;
        }

        cout << "Type exit To Cancel" << endl;
        cout << "Enter a number to choose an option: ";

        while (true) {
            cin >> input;
            if (input == "exit") {
                return;
            }

            try {
                choice = stoi(input);
                if (choice < 1 || choice > incomes.size()) {
                    cout << "Invalid selection. Please try again: ";
                } else {
                    IncomeItem& selected = incomes[choice - 1];
                    cout << "Enter new name: ";
                    cin >> newName;
                    if (newName == "exit") {
                        return;
                    }
                    cout << "Enter new amount $";

                    while (true) {
                        cin >> newAmountStr;

                        try {
                            newAmount = stof(newAmountStr);
                            cout << selected.category << " $" << selected.amount << " changed to: " << newName << " $" << newAmount << endl;
                            selected.category = newName;
                            selected.amount = newAmount;
                            return;
                        } catch (invalid_argument&) {
                            cout << "Invalid number. Please enter a valid amount: ";
                        }
                    }
                }
            } catch (invalid_argument&) {
                cout << "Please enter a valid number: ";
            }
        }
    }

    void addExpense(map<string, vector<ExpenseItem>>& expenseByMonth, const string& currentMonth) {
        ExpenseItem value;
        string strValue;
        cout << "Type exit To End" << endl;
        while (true) {
            cout << "Name Of Expense (Food, Rent, Utilities, Entertainment, Transportation, Etc): ";
            cin >> value.category;
            if (value.category == "exit" || value.category == "Exit") {
                break;
            };
            cout << "Enter Amount: $";
            while (true) {
                cin >> strValue;

                try {
                    value.amount = stoi(strValue);
                    expenseByMonth[currentMonth].push_back(value);
                    cout << "Added Sucessfully" << endl;
                    break;
                } catch (invalid_argument&) {
                    cout << "Invalid Number. Please Try Again: $";
                }
            }
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
    void removeExpense(const string& currentMonth, map<string, vector<ExpenseItem>>& expenseByMonth) {
        if (expenseByMonth.find(currentMonth) == expenseByMonth.end() || expenseByMonth[currentMonth].empty()) {
            cout << "No expense items for " << currentMonth << " to remove." << endl;
            return;
        }

        vector<ExpenseItem>& expenses = expenseByMonth[currentMonth];

        cout << "Expense items for " << currentMonth << ":" << endl;
        for (size_t i = 0; i < expenses.size(); ++i) {
            cout << i + 1 << ". " << expenses[i].category << " $" << expenses[i].amount << endl;
        }

        int intRemoveExpense;
        string strRemoveExpense;

        cout << "Type exit To Cancel" << endl;
        cout << "Enter a number to choose an option: ";
        while (true) {
            cin >> strRemoveExpense;
            if (strRemoveExpense == "exit") {
                return;
            }
            try {
                intRemoveExpense = stoi(strRemoveExpense);
                if (intRemoveExpense < 1 || intRemoveExpense > expenses.size()) {
                    cout << "Invalid selection. Please try again: ";
                } else {
                    ExpenseItem removedItem = expenses[intRemoveExpense - 1];
                    expenses.erase(expenses.begin() + (intRemoveExpense - 1));
                    cout << "Removed Expense: " << removedItem.category << " $" << removedItem.amount << endl;
                    break;
                }
            } catch (invalid_argument&) {
                cout << "Invalid option please enter a valid option: ";
            }
        }
    }
    void editExpense(map<string, vector<ExpenseItem>>& expenseByMonth, const string& currentMonth) {
        string newName, newAmountStr, input;
        float newAmount;
        int choice;

        vector<ExpenseItem>& expenses = expenseByMonth[currentMonth];

        if (expenses.empty()) {
            cout << "No Expenses Entries To Edit For " << currentMonth << "." << endl;
            return;
        }
        cout << "Expenses entries for " << currentMonth << ":" << endl;

        for (int i = 0; i < expenses.size(); ++i) {
            cout << i + 1 << ". " << expenses[i].category << " $" << expenses[i].amount << endl;
        }
        cout << "Type exit To Cancel" << endl;
        cout << "Enter a number to choose an option: ";

        while (true) {
            cin >> input;
            if (input == "exit") {
                return;
            }

            try {
                choice = stoi(input);
                if (choice < 1 || choice > expenses.size()) {
                    cout << "Invalid selection. Please try again: ";
                } else {
                    ExpenseItem& selected = expenses[choice - 1];
                    cout << "Enter new name: ";
                    cin >> newName;
                    if (newName == "exit") {
                        return;
                    }
                    cout << "Enter new amount $";

                    while (true) {
                        cin >> newAmountStr;

                        try {
                            newAmount = stof(newAmountStr);
                            cout << selected.category << " $" << selected.amount << " changed to: " << newName << " $" << newAmount << endl;
                            selected.category = newName;
                            selected.amount = newAmount;
                            return;
                        } catch (invalid_argument&) {
                            cout << "Invalid number. Please enter a valid amount: ";
                        }
                    }
                }
            } catch (invalid_argument&) {
                cout << "Please enter a valid number: ";
            }
        }
    }

    void removeMonth(vector<string>& months) {
        if (months.empty()) {
            cout << "No Months Have Been Added" << endl;
            return;
        }
        string strType;
        int intType;
        cout << "Choose which month to remove" << endl;
        for (int i = 0; i < months.size(); ++i) {
            cout << i + 1 << ". " << months[i] << endl;
        }
        cout << "Type exit To Cancel" << endl;
        cout << "Enter a number to choose an option: ";

        while (true) {
            cin >> strType;
            
            if (strType == "exit") {
                return;
            }

            try {
                intType = stoi(strType);
                if (intType >= 1 && intType <= months.size()) {
                    string removedMonth = months[intType - 1];
                    months.erase(months.begin() + (intType - 1));
                    cout << "Removed month: " << removedMonth << endl;
                    break;
                } else {
                    cout << "Invalid option please enter a valid option: ";
                }
            } catch (invalid_argument&) {
                cout << "Invalid option please enter a valid option: ";
            }
        }
    }
    void changeMonthName(vector<string>& months) {
        if (months.empty()) {
            cout << "No Months Have Been Added" << endl;
            return;
        }
        string strTemp;
        int intTemp;
        string newName;
        string oldName;
        cout << "Choose which month to change" << endl;
        for (int i = 0; i < months.size(); ++i) {
            cout << i + 1 << ". " << months[i] << endl;
        }
        cout << "Type exit To Cancel" << endl;
        cout << "Enter a number to choose an option: ";

        while (true) {
            cin >> strTemp;
            if (strTemp == "exit") {
                return;
            }

            try {
                intTemp = stoi(strTemp);
                if (intTemp >= 1 && intTemp <= months.size()) {
                    break;
                } else {
                    cout << "Invalid option please enter a valid option: ";
                }
            } catch (invalid_argument&) {
                cout << "Invalid option please enter a valid option: ";
            }        
        }
        oldName = months[intTemp - 1];
        cout << "Enter new month name: ";
        cin >> newName;
        months[intTemp - 1] = newName;
        cout << "Changed \"" << oldName << "\" to \"" << newName << "\"" << endl;
    };
    
};
class TrackerSettings {
    public:
        void addEditFile(TrackerModify& modify, map<string, vector<IncomeItem>>& incomeByMonth, map<string, vector<ExpenseItem>>& expenseByMonth, vector<string>& months,  string& currentMonth, int& year) {
            int intDecision;
            string strDecision;
            while (true) {
                cout << "1. Edit Year" << endl;
                cout << "2. Edit Month" << endl;
                cout << "3. Back" << endl;
                cout << "Enter a number to choose an option: ";
                while (true) {
                    cin >> strDecision;
                    try {
                        intDecision = stoi(strDecision);
                        if (intDecision < 1 || intDecision > 3) {
                            cout << "Invalid option please enter a valid option: ";
                        } else {
                            break;
                        }
                    } catch (invalid_argument&) {
                        cout << "Invalid option please enter a valid option: ";
                    }
                }
                if (intDecision == 1) {
                    modify.changeYear(year);
                } else if (intDecision == 2){
                    monthMenu(modify, incomeByMonth, expenseByMonth, months, currentMonth);
                } else {
                    break;
                }
            }

        }

        void monthMenu(TrackerModify& modify, map<string, vector<IncomeItem>>& incomeByMonth, map<string, vector<ExpenseItem>>& expenseByMonth, vector<string>& months, string& currentMonth) {
            int intAlternative;
            string strAlternative;
            while (true) {
                cout << "1. Add Month" << endl;
                cout << "2. Remove Month" << endl;
                cout << "3. Edit Month Name" << endl;
                cout << "4. Add To Month" << endl;
                cout << "5. Back" << endl;
                cout << "Enter a number to choose an option: ";
                while (true) {
                    cin >> strAlternative;
                    try {
                        intAlternative = stoi(strAlternative);
                        if (intAlternative < 1 || intAlternative > 5) {
                            cout << "Invalid option please enter a valid option: ";
                        } else {
                            break;
                        }
                    } catch (invalid_argument&) {
                        cout << "Invalid option please enter a valid option: ";

                    }
                }
                if (intAlternative == 1) {
                    modify.addMonth(months);
                } else if (intAlternative == 2) {
                    modify.removeMonth(months);
                } else if (intAlternative == 3) {
                    modify.changeMonthName(months);
                } else if (intAlternative == 4) {
                    addToMonth(modify, incomeByMonth, expenseByMonth, months, currentMonth);
                } else {
                    break;
                }
            }
        }
        void addToMonth(TrackerModify& modify, map<string, vector<IncomeItem>>& incomeByMonth, map<string, vector<ExpenseItem>>& expenseByMonth, vector<string>& months,  string& currentMonth) {
            if (months.empty()) {
                cout << "Please Enter A Month To Edit" << endl;
                return;
            }
            int intSelection;
            string strSelection;
            cout << "Available months: " << endl;
            for (int i = 0; i < months.size(); ++i) {
                cout << i + 1 << ". " << months[i] << endl;
            }
            cout << "Type exit To Cancel" << endl;
            cout << "Enter a number to choose an option: ";
            while (true) {
                cin >> strSelection;
                if (strSelection == "exit") {
                    return;
                }
                try {
                    intSelection = stoi(strSelection);
                    if (intSelection >= 1 && intSelection <= months.size()) {
                        currentMonth = months[intSelection - 1];
                        break;
                    } else {
                        cout << "Invalid selection. Please try again: ";
                    }
                } catch (invalid_argument&) {
                    cout << "Invalid option please enter a valid option: ";
                }
            }
            toggleTable(modify, incomeByMonth, expenseByMonth, months, currentMonth);


        };
        void toggleTable(TrackerModify& modify, map<string, vector<IncomeItem>>& incomeByMonth, map<string, vector<ExpenseItem>>& expenseByMonth, vector<string>& months, string& currentMonth) {
            int intAlt;
            string strAlt;
            while (true) {
                cout << "Editing: " << currentMonth << endl;
                cout << "1. Add Income" << endl;
                cout << "2. Remove Income" << endl;
                cout << "3. Edit Income" << endl;
                cout << "4. Add Expense" << endl;
                cout << "5. Remove Expense" << endl;
                cout << "6. Edit Expense" << endl;
                cout << "7. Exit" << endl;
                cout << "Enter a number to choose an option: ";
                while (true) {
                    cin >> strAlt;
                    try {
                        intAlt = stoi(strAlt);
                        if (intAlt < 1 || intAlt > 7) {
                            cout << "Invalid option please enter a valid option: ";
                        } else {
                            break;
                        }
                    } catch (invalid_argument&) {
                        cout << "Invalid option please enter a valid option: ";
                    }
                }
                if (intAlt == 1) {
                    modify.addIncome(incomeByMonth, currentMonth);
                } else if (intAlt == 2) {
                    modify.removeIncome(currentMonth, incomeByMonth);
                } else if (intAlt == 3) {
                    modify.editIncome(incomeByMonth, currentMonth);
                } else if (intAlt == 4) {
                    modify.addExpense(expenseByMonth, currentMonth);
                } else if (intAlt == 5) {
                    modify.removeExpense(currentMonth, expenseByMonth);
                } else if (intAlt == 6) {
                    modify.editExpense(expenseByMonth, currentMonth);
                } else {
                    break;
                }
            }
        }
        void viewReport(const map<string, vector<IncomeItem>>& incomeByMonth, const map<string, vector<ExpenseItem>>& expenseByMonth, vector<string> months, int year) {
            int monthCount = months.size();
            int columnWidth = 12;
            int totalWidth = (columnWidth * (monthCount + 2)) + 1;
            int yearLen = to_string(year).length();
            int totalColumns = months.size() + 2; // Category + months + total
            int totalTableWidth = totalColumns * (columnWidth + 1) + 1;  // each column + a '|' separator



            int yearLength = to_string(year).length();
            int padLeft = (totalTableWidth - 2 - yearLength) / 2;  // -2 for the edge '|'s
            int padRight = totalTableWidth - 2 - yearLength - padLeft;
                    
            cout << "|" << string(totalTableWidth - 2, '-') << "|" << endl;
            cout << "|" << string(padLeft, ' ') << year << string(padRight, ' ') << "|" << endl;
            cout << "|" << string(totalTableWidth - 2, '-') << "|" << endl;

            cout << "|" << left << setw(columnWidth) << "CATEGORY" << "|";

            for (const string& month : months) {
                cout << left << setw(columnWidth) << month.substr(0, columnWidth) << "|";
            }

            cout << left << setw(columnWidth) << "TOTAL" << "|" << endl;
            cout << "|" << string(totalTableWidth - 2, '-') << "|" << endl;

            cout << "|" << left << setw(columnWidth) << "INCOME" << "|";
            for (int i = 0; i < monthCount + 1; ++i) {
                cout << string(columnWidth, ' ') << "|";
            }
            cout << endl;
            cout << "|" << string(totalTableWidth - 2, '-') << "|" << endl;


            // Get all user-entered income categories
            vector<string> incomeCategories;
            for (const string& month : months) {
                if (incomeByMonth.count(month)) {
                    for (const IncomeItem& item : incomeByMonth.at(month)) {
                        if (find(incomeCategories.begin(), incomeCategories.end(), item.category) == incomeCategories.end()) {
                            incomeCategories.push_back(item.category);
                        }
                    }
                }
            }

            // Print each income category row
            for (const string& category : incomeCategories) {
                cout << "|" << left << setw(columnWidth) << category << "|";
                float totalCategory = 0.0;
            
                for (const string& month : months) {
                    float sum = 0.0;
                    if (incomeByMonth.count(month)) {
                        for (const IncomeItem& item : incomeByMonth.at(month)) {
                            if (item.category == category) {
                                sum += item.amount;
                            }
                        }
                    }
                    totalCategory += sum;
                    cout << left << setw(columnWidth) << fixed << setprecision(2) << sum << "|";
                }
            
                cout << left << setw(columnWidth) << fixed << setprecision(2) << totalCategory << "|" << endl;
                cout << "|" << string(totalTableWidth - 2, '-') << "|" << endl;
            }

            // Print "Total Income" row
            cout << "|" << left << setw(columnWidth) << "Total Income" << "|";
            cout << "|" << string(totalTableWidth - 2, '-') << "|" << endl;
            float grandTotal = 0.0;

            for (const string& month : months) {
                float monthTotal = 0.0;
                if (incomeByMonth.count(month)) {
                    for (const IncomeItem& item : incomeByMonth.at(month)) {
                        monthTotal += item.amount;
                    }
                }
                grandTotal += monthTotal;
                cout << left << setw(columnWidth) << fixed << setprecision(2) << monthTotal << "|";
            }

            cout << left << setw(columnWidth) << fixed << setprecision(2) << grandTotal << "|" << endl;


        }
        void exportFile() {

        };
        void resetFile(map<string, vector<IncomeItem>>& incomeByMonth, map<string, vector<ExpenseItem>>& expenseByMonth, vector<string> months, int year, bool& resetFile) {
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
            incomeByMonth.clear();
            expenseByMonth.clear();
            months.clear();
            year = 0;
            cout << "Sucessfully Reset file" << endl;
            resetFile = true;
        }

};

void showMenu(TrackerModify& modify, TrackerSettings& settings, map<string, vector<IncomeItem>>& incomeByMonth, map<string, vector<ExpenseItem>>& expenseByMonth, vector<string>& months,  string& currentMonth, int& year, bool& resetFile) {
    int intOption;
    string strOption;
    cout << "1. Add/Edit File" << endl;
    cout << "2. View Report" << endl;
    cout << "3. Export File" << endl;
    cout << "4. Reset File" << endl;
    cout << "Enter a number to choose an option: ";
    while (true) {
        cin >> strOption;

        try {
            intOption = stoi(strOption);
            if (intOption < 1 || intOption > 4) {
                cout << "Invalid option please enter a valid option: ";
            } else {
                break;
            }
        } catch (invalid_argument&) {
            cout << "Invalid Option please enter a valid option: ";
        }
    }
    if (intOption == 1) {
        settings.addEditFile(modify, incomeByMonth, expenseByMonth, months, currentMonth, year);
    } else if (intOption == 2) {
        settings.viewReport(incomeByMonth, expenseByMonth, months, year);
    } else if (intOption == 3) {
        cout << "placeholder";
    } else {
        settings.resetFile(incomeByMonth, expenseByMonth, months, year, resetFile);
    }
}


int main() {
    string tempYear;
    int year;
    string currentMonth;
    map<string, vector<IncomeItem>> incomeByMonth;
    map<string, vector<ExpenseItem>> expenseByMonth;
    vector<string> months;
    bool resetFile = false;
    TrackerModify modify;
    TrackerSettings settings;


    cout << "Welcome To Your Personal Finance Tracker" << endl;
    cout << "Enter The Year: (2025, 2026, etc): ";

    while (true) {
        cin >> tempYear;

        try {
            year = stoi(tempYear);
            break;
        }  catch (invalid_argument&) {
            cout << "Invalid Number. Please Enter A Valid Year: ";
        }
    }

    while (true) {
        if (resetFile) {
            cout << "Welcome To Your Personal Finance Tracker" << endl;
            cout << "Enter The Year: (2025, 2026, etc): ";
            cin >> year;
            resetFile = false;    
        }

        showMenu(modify, settings, incomeByMonth, expenseByMonth, months, currentMonth, year, resetFile);
    }

    return 0;
}