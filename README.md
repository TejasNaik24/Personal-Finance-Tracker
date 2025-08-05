# Personal Finance Tracker

A Personal Finance tracker written in **C++**. It allows users to keep track of their monthly income and expenses, 
edit financial data, generate monthly reports, and export financial data to CSV. The program demonstrates 
**object-oriented programming**, **file I/O**, **data formatting**, and **robust user input handling**.

### Check out the demo [here](https://drive.google.com/file/d/1nWzTE9D0tjEIfbEN6k0OqfCOIK7urn3Y/view?usp=sharing)!


## Features

- **Monthly Tracking**: Add, edit, rename, or delete months  
- **Income Tracking**: Add, edit, or remove income entries by category  
- **Expense Tracking**: Add, edit, or remove expense entries by category  
- **Report Generation**: View monthly financial reports formatted in a clean table layout  
- **CSV Export**: Export all finance data to a structured file for spreadsheet use  
- **Input Validation**: Handles invalid inputs gracefully  


## Sample Categories

- **Income**: Salary, Freelance, Side Gigs, Bonuses, Tips, Rental, Dividends  
- **Expenses**: Food, Rent, Utilities, Entertainment, Transportation  


## Technologies Used

- Language: **C++**
- Concepts: **OOP**, **File I/O**, **Maps**, **Vectors**, **Input Parsing**, **String Manipulation**
- Libraries:
  ```cpp
  #include <iostream>
  #include <vector>
  #include <map>
  #include <string>
  #include <fstream>
  #include <sstream>
  #include <iomanip>
  #include <stdexcept>
  ```


## How to Use

In order to run the program:

1. Make sure you have a C++ compiler installed (like `g++`).
2. Open your terminal in the project directory.
3. To compile the program, run:
   ```bash
   g++ -std=c++11 main.cpp -o main
   ```
4. To run the program, use:
   ```bash
   ./main
   ```

5. Follow the **menu prompts** to add months, income, expenses, or generate reports.


## Sample Menu Output

```sh
Welcome To Your Personal Finance Tracker
Enter The Year: (2025, 2026, etc): 2025
1. Add/Edit File
2. View Report
3. Export File
4. Reset File
5. Exit
Enter a number to choose an option: 1
1. Edit Year
2. Edit Month
3. View Report
4. Back
Enter a number to choose an option: 2
1. Add Month
2. Remove Month
3. Edit Month Name
4. Add To Month
5. View Report
6. Back
Enter a number to choose an option: 4
Please Enter A Month To Edit
1. Add Month
2. Remove Month
3. Edit Month Name
4. Add To Month
5. View Report
6. Back
Enter a number to choose an option: 1
Enter the month: (January, February, etc): January
1. Add Month
2. Remove Month
3. Edit Month Name
4. Add To Month
5. View Report
6. Back
Enter a number to choose an option: 4
Available months: 
1. January
Type exit To Cancel
Enter a number to choose an option: 1
Editing: January
1. Add Income
2. Remove Income
3. Edit Income
4. Add Expense
5. Remove Expense
6. Edit Expense
7. View Report
8. Exit
Enter a number to choose an option: 1
Type Exit To End
Name Of Income (Salary, Freelance, Side Gigs, Bonuses, Tips, Rental, Dividends, Etc): Salary
Enter amount: $400
Added Sucessfully
Name Of Income (Salary, Freelance, Side Gigs, Bonuses, Tips, Rental, Dividends, Etc): exit
Editing: January
1. Add Income
2. Remove Income
3. Edit Income
4. Add Expense
5. Remove Expense
6. Edit Expense
7. View Report
8. Exit
Enter a number to choose an option: 4
Type Exit To End
Name Of Expense (Food, Rent, Utilities, Entertainment, Transportation, Etc): Food
Enter Amount: $500
Added Sucessfully
Name Of Expense (Food, Rent, Utilities, Entertainment, Transportation, Etc): exit
Editing: January
1. Add Income
2. Remove Income
3. Edit Income
4. Add Expense
5. Remove Expense
6. Edit Expense
7. View Report
8. Exit
Enter a number to choose an option: 
```
## Sample Data Output

```sh
|-------------------------------------------------------------------|
|2025                                                               |
|-------------------------------------------------------------------|
|Category        |January         |February        |Total           |
|-------------------------------------------------------------------|
|Income                                                             |
|-------------------------------------------------------------------|
|Salary          |$3000.00        |$0.00           |$3000.00        |
|-------------------------------------------------------------------|
|Freelance       |$0.00           |$3412.00        |$3412.00        |
|-------------------------------------------------------------------|
|Total Income    |$3000.00        |$3412.00        |$6412.00        |
|-------------------------------------------------------------------|
|Expenses                                                           |
|-------------------------------------------------------------------|
|Food            |$500.00         |$0.00           |$500.00         |
|-------------------------------------------------------------------|
|Rent            |$0.00           |$123.00         |$123.00         |
|-------------------------------------------------------------------|
|Total Expenses  |$500.00         |$123.00         |$623.00         |
|-------------------------------------------------------------------|
|Net Saving      |$2500.00        |$3289.00        |$5789.00        |
|-------------------------------------------------------------------|

```

## File Structure

- `main` — Main program logic and entry point  
- `TrackerSettings` — Handles data storage, reporting, and CSV export  
- `TrackerModify` — Manages all income, expense, and month modification operations


