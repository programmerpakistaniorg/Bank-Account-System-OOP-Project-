# Bank Management System

A console-based banking application built in C++ that allows users to create accounts, deposit and withdraw money, and view account details. The system supports both Savings and Current accounts, with interest calculation and minimum balance enforcement.

---

## 🚀 Features

- Create new bank accounts (Savings or Current)
- Deposit money with interest (10% for Savings, 0% for Current)
- Withdraw money with minimum balance enforcement (1000 Rs)
- View account details (name, contact, balance, etc.)
- File-based data persistence using `user_acc_details.txt`
- Operator overloading for deposit (`+=`) and withdrawal (`-=`) logic
- Polymorphic behavior for account types
- Input validation and error handling

---

## 🧱 Class Structure

### `Account` (Base Class)
- Attributes: `name`, `accountNumber`, `address`, `contact`, `balance`, `accountType`
- Methods:
  - `createAccount()`
  - `deposit()`, `withdraw()`
  - `displayInfo()`, `loadAccount()`
  - `operator+=`, `operator-=`
  - `calculateInterest()` (virtual)

### `savingsAccount` (Derived)
- Overrides `calculateInterest()` → returns 10% of deposit

### `currentAccount` (Derived)
- Overrides `calculateInterest()` → returns 0%

---

## 📁 File Structure

- `banksystemprogram.cpp` — main source code
- `user_acc_details.txt` — stores account data persistently

---

## 🧪 How to Run

1. Compile the program:
   ```bash
   g++ banksystemprogram.cpp -o bank
- Run the executable:
    `./bank`
- Follow the menu prompts to interact with the system.
📌 Notes- Minimum balance of 1000 Rs is enforced for all account types.
- Interest is applied only during deposits for Savings accounts.
- Account numbers are randomly generated and prefixed with PK.
## 📊 UML Diagram
- The system includes a UML class diagram showing inheritance and method structure.
- (See attached UML image in the project folder)
## 🙌 Author
Muhammad Tayyab 😎

BS Software Engineering — Virtual University of Pakistan

Intern at TechnoDevs Software House, Lahore

Aspiring SaaS founder and tech educator

## 📜 License
This project is for educational purposes and personal portfolio use. Feel free to modify and extend it.
