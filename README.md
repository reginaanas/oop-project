# 📚 ShelfMate: Library Management System

Welcome to **ShelfMate**! 👋

ShelfMate is a simple, terminal-based Library Management System built with **C++** to demonstrate the four pillars of Object-Oriented Programming (OOP): encapsulation, abstraction, inheritance, and polymorphism.

The application allows administrators to manage library items and members, while members can borrow and return books or magazines. It also calculates late return fees automatically. 💻

## ✨ Features

### 🔐 Login System
* Admin login using the ID `ADMIN001`.
* Member login using their registered member ID.
* Simple ID-based authentication without passwords.

### 📖 Library Collection
* View all available and borrowed items.
* Search for items by title.
* Add new books and magazines as an administrator.
* Display item details and borrowing status.

### 👥 Member Management
* Register new library members.
* View the list of registered members.
* Each member has a unique ID.

### 🔄 Borrowing and Returning
* Borrow available library items.
* Return borrowed items.
* Set a borrowing period of **7 days**.
* Prevent members from borrowing items that are already borrowed.
* Prevent members from returning items borrowed by someone else.

### 💰 Automatic Late Fee Calculation
ShelfMate calculates late fees based on the type of library item.
| Item Type   |        Late Fee |
| ----------- | --------------: |
| 📘 Book     | Rp1,000 per day |
| 📰 Magazine |   Rp500 per day |

No late fee is charged when an item is returned on or before its due date.

### 🗓️ Date Simulation
* Use the actual current date or enter a simulated date.
* Test overdue returns without waiting for the actual due date.
* View the number of overdue days and the calculated fine.

### 🧾 Transaction History
* Administrators can view all loan transactions.
* Members can view their own transaction history.
* Transaction records include borrowing dates, due dates, return dates, fines, and transaction status.

## 🧠 OOP Concepts
ShelfMate demonstrates the four fundamental pillars of Object-Oriented Programming.
| OOP Pillar           | Implementation                                                                                      |
| -------------------- | --------------------------------------------------------------------------------------------------- |
| **Encapsulation** 🔒 | Classes use private attributes and public methods to control access to data.                        |
| **Abstraction** 🎭   | `LibraryItem` is an abstract base class with pure virtual functions.                                |
| **Inheritance** 🌱   | `Book` and `Magazine` inherit from `LibraryItem`.                                                   |
| **Polymorphism** 🔀  | The `calculateLateFee()` and `displayInfo()` methods behave differently depending on the item type. |

## 🏗️ Class Overview
* `LibraryItem` — Abstract base class for library items.
* `Book` — Represents books and defines the book late fee.
* `Magazine` — Represents magazines and defines the magazine late fee.
* `Member` — Stores member information.
* `Loan` — Stores borrowing and return transaction details.
* `Library` — Manages items, members, transactions, menus, and library operations.

## 🚀 Getting Started

### Requirements
* A C++ compiler that supports **C++11 or later**.
* A terminal or command-line interface.
* Visual Studio Code or another code editor (optional).

### 1. Clone or Download the Project
Download the project files and open the project folder in your terminal.

### 2. Compile the Program
Run the following command:
```bash
g++ -std=c++11 project.cpp -o project
```

### 3. Run ShelfMate
**Windows:**

```bash
.\project.exe
```

**Linux or macOS:**

```bash
./project
```

## 🔑 Sample Login Accounts
The application includes sample accounts for testing.
| Role             | Login ID   | Name                  |
| ---------------- | ---------- | --------------------- |
| 👑 Administrator | `ADMIN001` | Admin                 |
| 👩‍🎓 Member     | `MBR001`   | Nida Nur Hafizhah     |
| 👩‍🎓 Member     | `MBR002`   | Regina Titian Pinasti |

No password is required.

## 📚 Sample Library Items
| Item ID | Type        | Title                    | Author / Issue   |
| ------- | ----------- | ------------------------ | ---------------- |
| `B001`  | 📘 Book     | Clean Code               | Robert C. Martin |
| `B002`  | 📘 Book     | The Pragmatic Programmer | Andrew Hunt      |
| `M001`  | 📰 Magazine | Tech Monthly             | October 2026     |

## 🧪 Testing the Late Fee Feature
You can test the late fee calculation using simulated dates.

**Example: Returning a book late**
1. Log in as member `MBR001`.
2. Select the borrowing menu and borrow item `B001`.
3. When asked `Use simulated date? (y/n):`, enter `y`.
4. Enter the borrowing date: `2026-10-01`.
5. The system should calculate the due date as `2026-10-08`.
6. Select the return menu and return item `B001`.
7. Choose `y` again and enter the return date: `2026-10-11`.

Expected result:
```text
Due date: 2026-10-08
Return date: 2026-10-11
Days overdue: 3
Late fee: Rp3000
```

🎉 **Result:** The book is returned three days late, so the total fine is Rp3,000.
For comparison, returning magazine `M001` three days late results in a fine of Rp1,500.

## ⚠️ Limitations
* Data is stored in memory and is reset when the program closes.
* Login authentication uses member IDs without passwords.
* The application runs in the terminal and does not include a graphical user interface.
* Date simulation is intended for testing and demonstration purposes.
