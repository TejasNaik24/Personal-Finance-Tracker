#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <cctype>

using namespace std;

struct IncomeItem {
    string category;
    float amount;
};

struct ExpenseItem {
    string category;
    float amount;
};

string toTitleCase(string s) {
    if (s.empty()) {
        return s;
    }

    for (char &c : s) {
        c = tolower(static_cast<unsigned char>(c));
    }

    s[0] = toupper(static_cast<unsigned char>(s[0]));

    for (size_t i = 1; i < s.length(); ++i) {
        if (s[i-1] == ' ' && isalpha(static_cast<unsigned char>(s[i]))) {
            s[i] = toupper(static_cast<unsigned char>(s[i]));
        }
    }
    return s;
}

class TrackerSettings;

class TrackerModify {
private:
    TrackerSettings& settings;

public:
    TrackerModify(TrackerSettings& s) : settings(s) {}

    void addMonth();
    void addIncome();
    void removeIncome();
    void editIncome();
    void addExpense();
    void changeYear();
    void removeExpense();
    void editExpense();
    void removeMonth();
    void changeMonthName();
};

class TrackerSettings {
private:
    int year;
    string currentMonth;
    map<string, vector<IncomeItem>> incomeByMonth;
    map<string, vector<ExpenseItem>> expenseByMonth;
    vector<string> months;
    bool resetFile = false;
    bool end = false;

public:
    TrackerSettings() : year(0) {}

    map<string, vector<IncomeItem>>& getIncomeByMonthMutable() { return incomeByMonth; }
    map<string, vector<ExpenseItem>>& getExpenseByMonthMutable() { return expenseByMonth; }
    vector<string>& getMonthsMutable() { return months; }
    int& getYearMutable() { return year; }
    string& getCurrentMonthMutable() { return currentMonth; }
    bool getEndStatus() const { return end; }

    void addEditFile(TrackerModify& modify);
    void monthMenu(TrackerModify& modify);
    void addToMonth(TrackerModify& modify);
    void toggleTable(TrackerModify& modify);
    void viewReport();
    void exportFile();
    void resetFileFunction();
    void endCode();
};

void TrackerModify::addMonth() {
    string month;
    cout << "Enter the month: (January, February, etc): ";
    cin >> month;
    month = toTitleCase(month);
    settings.getMonthsMutable().push_back(month);
}

void TrackerModify::addIncome() {
    IncomeItem item;
    string strAmount;
    cout << "Type Exit To End" << endl;
    while (true) {
       cout << "Name Of Income (Salary, Freelance, Side Gigs, Bonuses, Tips, Rental, Dividends, Etc): ";
        cin >> item.category;
        item.category = toTitleCase(item.category);
        if (item.category == "Exit") {
            break;
        }
        cout << "Enter amount: $";
        while (true) {
            cin >> strAmount;
            try {
                item.amount = stof(strAmount);
                settings.getIncomeByMonthMutable()[settings.getCurrentMonthMutable()].push_back(item);
                cout << "Added Sucessfully" << endl;
                break;
            } catch (invalid_argument&) {
                 cout << "Invalid Number. Please Try Again: $";
            }
        }
    }
}

void TrackerModify::removeIncome() {
    string currentMonth = settings.getCurrentMonthMutable();
    map<string, vector<IncomeItem>>& incomeByMonth = settings.getIncomeByMonthMutable();

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

void TrackerModify::editIncome() {
    string currentMonth = settings.getCurrentMonthMutable();
    map<string, vector<IncomeItem>>& incomeByMonth = settings.getIncomeByMonthMutable();
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
                newName = toTitleCase(newName);
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

void TrackerModify::addExpense() {
    ExpenseItem value;
    string strValue;
    cout << "Type exit To End" << endl;
    while (true) {
        cout << "Name Of Expense (Food, Rent, Utilities, Entertainment, Transportation, Etc): ";
        cin >> value.category;
        value.category = toTitleCase(value.category);
        if (value.category == "Exit") {
            break;
        }
        cout << "Enter Amount: $";
        while (true) {
            cin >> strValue;

            try {
                value.amount = stof(strValue);
                settings.getExpenseByMonthMutable()[settings.getCurrentMonthMutable()].push_back(value);
                cout << "Added Sucessfully" << endl;
                break;
            } catch (invalid_argument&) {
                cout << "Invalid Number. Please Try Again: $";
            }
        }
    }
}

void TrackerModify::changeYear() {
    int& year = settings.getYearMutable();
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

void TrackerModify::removeExpense() {
    string currentMonth = settings.getCurrentMonthMutable();
    map<string, vector<ExpenseItem>>& expenseByMonth = settings.getExpenseByMonthMutable();

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

void TrackerModify::editExpense() {
    string currentMonth = settings.getCurrentMonthMutable();
    map<string, vector<ExpenseItem>>& expenseByMonth = settings.getExpenseByMonthMutable();
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
                newName = toTitleCase(newName);
                if (newName == "Exit") {
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

void TrackerModify::removeMonth() {
    vector<string>& months = settings.getMonthsMutable();
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

void TrackerModify::changeMonthName() {
    vector<string>& months = settings.getMonthsMutable();
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
    newName = toTitleCase(newName);
    months[intTemp - 1] = newName;
    cout << "Changed \"" << oldName << "\" to \"" << newName << "\"" << endl;
}

void TrackerSettings::addEditFile(TrackerModify& modify) {
    int intDecision;
    string strDecision;
    while (true) {
        cout << "1. Edit Year" << endl;
        cout << "2. Edit Month" << endl;
        cout << "3. View Report" << endl;
        cout << "4. Back" << endl;
        cout << "Enter a number to choose an option: ";
        while (true) {
            cin >> strDecision;
            try {
                intDecision = stoi(strDecision);
                if (intDecision < 1 || intDecision > 4) {
                    cout << "Invalid option please enter a valid option: ";
                } else {
                    break;
                }
            } catch (invalid_argument&) {
                cout << "Invalid option please enter a valid option: ";
            }
        }
        if (intDecision == 1) {
            modify.changeYear();
        } else if (intDecision == 2) {
            monthMenu(modify);
        } else if (intDecision == 3) {
            viewReport();
        } else {
            break;
        }
    }
}

void TrackerSettings::monthMenu(TrackerModify& modify) {
    int intAlternative;
    string strAlternative;
    while (true) {
        cout << "1. Add Month" << endl;
        cout << "2. Remove Month" << endl;
        cout << "3. Edit Month Name" << endl;
        cout << "4. Add To Month" << endl;
        cout << "5. View Report" << endl;
        cout << "6. Back" << endl;
        cout << "Enter a number to choose an option: ";
        while (true) {
            cin >> strAlternative;
            try {
                intAlternative = stoi(strAlternative);
                if (intAlternative < 1 || intAlternative > 6) {
                    cout << "Invalid option please enter a valid option: ";
                } else {
                    break;
                }
            } catch (invalid_argument&) {
                cout << "Invalid option please enter a valid option: ";
            }
        }
        if (intAlternative == 1) {
            modify.addMonth();
        } else if (intAlternative == 2) {
            modify.removeMonth();
        } else if (intAlternative == 3) {
            modify.changeMonthName();
        } else if (intAlternative == 4) {
            addToMonth(modify);
        } else if (intAlternative == 5) {
            viewReport();
        } else {
            break;
        }
    }
}

void TrackerSettings::addToMonth(TrackerModify& modify) {
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
    toggleTable(modify);
}

void TrackerSettings::toggleTable(TrackerModify& modify) {
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
        cout << "7. View Report" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter a number to choose an option: ";
        while (true) {
            cin >> strAlt;
            try {
                intAlt = stoi(strAlt);
                if (intAlt < 1 || intAlt > 8) {
                    cout << "Invalid option please enter a valid option: ";
                } else {
                    break;
                }
            } catch (invalid_argument&) {
                cout << "Invalid option please enter a valid option: ";
            }
        }
        if (intAlt == 1) {
            modify.addIncome();
        } else if (intAlt == 2) {
            modify.removeIncome();
        } else if (intAlt == 3) {
            modify.editIncome();
        } else if (intAlt == 4) {
            modify.addExpense();
        } else if (intAlt == 5) {
            modify.removeExpense();
        } else if (intAlt == 6) {
            modify.editExpense();
        } else if (intAlt == 7) {
            viewReport();
        } else {
            break;
        }
    }
}

void TrackerSettings::viewReport() {
    int monthCount = months.size();
    int columnWidth = 16;
    int totalWidth = (columnWidth * (monthCount + 2)) + 1;
    int yearLen = to_string(year).length();
    int totalColumns = months.size() + 2;
    int totalTableWidth = totalColumns * (columnWidth + 1) + 1;


    int yearLength = to_string(year).length();
    int padLeft = (totalTableWidth - 2 - yearLength) / 2;
    int padRight = totalTableWidth - 2 - yearLength - padLeft;

    cout << "|" << string(totalTableWidth - 2, '-') << "|" << endl;
    cout << "|" << string(padLeft, ' ') << year << string(padRight, ' ') << "|" << endl;
    cout << "|" << string(totalTableWidth - 2, '-') << "|" << endl;

    cout << "|" << left << setw(columnWidth) << "Category" << "|";

    for (const string& month : months) {
        cout << left << setw(columnWidth) << month.substr(0, columnWidth) << "|";
    }

    cout << left << setw(columnWidth) << "Total" << "|" << endl;
    cout << "|" << string(totalTableWidth - 2, '-') << "|" << endl;

    if (!incomeByMonth.empty()) {
        cout << "|" << left << setw(columnWidth) << "Income";
        for (int i = 0; i < monthCount + 1; ++i) {
            cout << string(columnWidth, ' ') << " ";
        }
        cout << "|" << endl;
        cout << "|" << string(totalTableWidth - 2, '-') << "|" << endl;


        vector<string> incomeCategories;
        for (const string& month : months) {
            if (incomeByMonth.count(month)) {
                for (const IncomeItem& item : incomeByMonth.at(month)) {
                    // Replaced std::find with manual loop as per your strict no new include rule
                    bool found = false;
                    for (const string& existingCategory : incomeCategories) {
                        if (existingCategory == item.category) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        incomeCategories.push_back(item.category);
                    }
                }
            }
        }

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

        cout << "|" << left << setw(columnWidth) << "Total Income" << "|";
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
        cout << "|" << string(totalTableWidth - 2, '-') << "|" << endl;
    } else {
        cout << "|" << left << setw(columnWidth) << "No Income Data";
        for (int i = 0; i < monthCount + 1; ++i) {
            cout << string(columnWidth, ' ') << " ";
        }
        cout << "|" << endl;
        cout << "|" << string(totalTableWidth - 2, '-') << "|" << endl;
    }
    if (!expenseByMonth.empty()) {
        cout << "|" << left << setw(columnWidth) << "Expenses";
        for (int i = 0; i < monthCount + 1; ++i) {
            cout << string(columnWidth, ' ') << " ";
        }
        cout << "|" << endl;
        cout << "|" << string(totalTableWidth - 2, '-') << "|" << endl;

        vector<string> expensesCategories;
        for (const string& month : months) {
            if (expenseByMonth.count(month)) {
                for (const ExpenseItem& value : expenseByMonth.at(month)) {
                    // Replaced std::find with manual loop as per your strict no new include rule
                    bool found = false;
                    for (const string& existingCategory : expensesCategories) {
                        if (existingCategory == value.category) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        expensesCategories.push_back(value.category);
                    }
                }
            }
        }


        for (const string& category : expensesCategories) {
            cout << "|" << left << setw(columnWidth) << category << "|";
            float totalCategory = 0.0;

            for (const string& month : months) {
                float sum = 0.0;
                if (expenseByMonth.count(month)) {
                    for (const ExpenseItem& value : expenseByMonth.at(month)) {
                        if (value.category == category) {
                            sum += value.amount;
                        }
                    }
                }
                totalCategory += sum;
                cout << left << setw(columnWidth) << fixed << setprecision(2) << sum << "|";
            }

            cout << left << setw(columnWidth) << fixed << setprecision(2) << totalCategory << "|" << endl;
            cout << "|" << string(totalTableWidth - 2, '-') << "|" << endl;
        }

        cout << "|" << left << setw(columnWidth) << "Total Expenses" << "|";
        float grandTotal = 0.0;
        for (const string& month : months) {
            float monthTotal = 0.0;
            if (expenseByMonth.count(month)) {
                for (const ExpenseItem& item : expenseByMonth.at(month)) {
                    monthTotal += item.amount;
                }
            }
            grandTotal += monthTotal;
            cout << left << setw(columnWidth) << fixed << setprecision(2) << monthTotal << "|";
        }
        cout << left << setw(columnWidth) << fixed << setprecision(2) << grandTotal << "|" << endl;
        cout << "|" << string(totalTableWidth - 2, '-') << "|" << endl;
    } else {
        cout << "|" << left << setw(columnWidth) << "No Expenses Data";
        for (int i = 0; i < monthCount + 1; ++i) {
            cout << string(columnWidth, ' ') << " ";
        }
        cout << "|" << endl;
        cout << "|" << string(totalTableWidth - 2, '-') << "|" << endl;

    }
    if (!incomeByMonth.empty() || !expenseByMonth.empty()) {
        cout << "|" << left << setw(columnWidth) << "Net Saving" << "|";
        float TotalNetSaving = 0.0;

        for (const string& month : months) {
            float totalIncome = 0.0;
            float totalExpenses = 0.0;
            if (incomeByMonth.count(month)) {
                for (const IncomeItem& item : incomeByMonth.at(month)) {
                    totalIncome += item.amount;
                }
            }

            if (expenseByMonth.count(month)) {
                for (const ExpenseItem& item : expenseByMonth.at(month)) {
                    totalExpenses += item.amount;
                }
            }

            float netSaving = totalIncome - totalExpenses;
            TotalNetSaving += netSaving;
            cout << setw(columnWidth) << fixed << setprecision(2) << netSaving << "|";
        }
        cout << left << setw(columnWidth) << fixed << setprecision(2) << TotalNetSaving << "|" << endl;
        cout << "|" << string(totalTableWidth - 2, '-') << "|" << endl;
    }
}

void TrackerSettings::exportFile() {
}

void TrackerSettings::resetFileFunction() {
    string choice;
    cout << "Are you sure you want to reset your file? (This Will Reset Everything) y/n: ";
    cin >> choice;
    while (choice != "n" && choice != "N" && choice != "y" && choice != "Y") {
        cout << "Invalid option please enter a valid option: ";
        cin >> choice;
    }
    if (choice == "n" || choice == "N") {
        return;
    }
    months.clear();
    incomeByMonth.clear();
    expenseByMonth.clear();
    year = 0;
    cout << "Sucessfully Reset file" << endl;
    resetFile = true;
}

void TrackerSettings::endCode() {
    string done;
    cout << "Are you sure you want to exit? (All data will be lost) y/n: ";
    cin >> done;
    while (done != "n" && done != "N" && done != "y" && done != "Y") {
        cout << "Invalid option please enter a valid option: ";
        cin >> done;
    }
    if (done == "n" || done == "N") {
        return;
    }
    end = true;
}

void showMenu(TrackerModify& modify, TrackerSettings& settings) {
    int intOption;
    string strOption;
    cout << "1. Add/Edit File" << endl;
    cout << "2. View Report" << endl;
    cout << "3. Export File" << endl;
    cout << "4. Reset File" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter a number to choose an option: ";
    while (true) {
        cin >> strOption;

        try {
            intOption = stoi(strOption);
            if (intOption < 1 || intOption > 5) {
                cout << "Invalid option please enter a valid option: ";
            } else {
                break;
            }
        } catch (invalid_argument&) {
            cout << "Invalid Option please enter a valid option: ";
        }
    }
    if (intOption == 1) {
        settings.addEditFile(modify);
    } else if (intOption == 2) {
        settings.viewReport();
    } else if (intOption == 3) {
        settings.exportFile();
    } else if (intOption == 4) {
        settings.resetFileFunction();
    } else if (intOption == 5) {
        settings.endCode();
    }
}

int main() {
    TrackerSettings settings;
    TrackerModify modify(settings);
    string yearInput;

    cout << "Welcome To Your Personal Finance Tracker" << endl;
    cout << "Enter The Year: (2025, 2026, etc): ";

    while (true) {
        cin >> yearInput;

        try {
            settings.getYearMutable() = stoi(yearInput);
            break;
        } catch (invalid_argument&) {
            cout << "Invalid Number. Please Enter A Valid Year: ";
        }
    }

    while (!settings.getEndStatus()) {
        showMenu(modify, settings);
    }

    return 0;
}