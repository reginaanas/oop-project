# 📚 ShelfMate: Library Management System

Welcome to ShelfMate! 👋

ShelfMate is a terminal-based Library Management System built with C++11 to demonstrate the four pillars of Object-Oriented Programming (OOP), along with permanent file-based storage.
The application allows administrators to manage library items and members, while members can borrow and return books or magazines. It automatically calculates late return fees and persists all data across program runs. 💻

## ✨ Features

### 🔐 Login System
- Admin login using the ID `ADMIN001`.
- Member login using their registered member ID.
- Simple ID-based authentication without passwords.

### 💾 Permanent File Storage (TXT Persistence)
- Automatically saves and loads data using plain text files (`items.txt`, `members.txt`, and `loans.txt`).
- Real-time file synchronization after adding items, registering members, or completing transactions.
- Auto-incrementing ID generation for books (`B001`), magazines (`M001`), and members (`MBR001`) based on stored data.
- First-run auto-seeding mechanism when storage files do not yet contain data.

### 📖 Library Collection
- View all available and borrowed items.
- Search for items by title.
- Add new books and magazines as an administrator.
- Display item details and borrowing status.

### 👥 Member Management
- Register new library members.
- View the list of registered members.
- Assign a unique ID to each member.

### 🔄 Borrowing and Returning
- Borrow available library items.
- Return borrowed items.
- Set a borrowing period of 7 days.
- Prevent members from borrowing items that are already borrowed.
- Prevent members from returning items borrowed by someone else.

### 💰 Automatic Late Fee Calculation
ShelfMate calculates late fees based on the type of library item:

- **Book:** Rp1,000 per day.
- **Magazine:** Rp500 per day.

No late fee is charged when an item is returned on or before its due date.

### 🗓️ Date Simulation
- Use the actual current date or enter a simulated date.
- Test overdue returns without waiting for the actual due date.
- View the number of overdue days and the calculated fine.

### 🧾 Transaction History
- Administrators can view all loan transactions.
- Members can view their own transaction history.
- Transaction records include borrowing dates, due dates, return dates, fines, and transaction status.

## 🧠 OOP Concepts
ShelfMate demonstrates the four fundamental principles of Object-Oriented Programming:
- **Encapsulation 🔒:** Attributes are kept private, with public getter and setter methods used to control access.
- **Abstraction 🎭:** `LibraryItem` is an abstract base class containing pure virtual functions, including `getType()`, `displayInfo()`, `calculateLateFee()`, and `serialize()`.
- **Inheritance 🌱:** `Book` and `Magazine` inherit from the `LibraryItem` base class.
- **Polymorphism 🔀:** Functions such as `calculateLateFee()`, `displayInfo()`, and `serialize()` behave differently depending on whether the item is a `Book` or a `Magazine`.

## 📁 Storage File Structures
ShelfMate stores its data in three plain text files located in the program's working directory.

### 1. `items.txt`
Stores library item information.

```text
Type|ID|Title|Author or Issue|isBorrowed(0/1)|BorrowerID
```

Example:

```text
Book|B001|Clean Code|Robert C. Martin|0|
Magazine|M001|Tech Monthly|October 2026|1|MBR001
```

### 2. `members.txt`
Stores registered member information.

```text
MemberID|MemberName
```

Example:

```text
MBR001|Nida Nur Hafizhah
MBR002|Regina Titian Pinasti
```

### 3. `loans.txt`
Stores borrowing and returning transaction records.

```text
MemberID|ItemID|BorrowDate|DueDate|ReturnDate|FineAmount|isReturned(0/1)
```

Example:

```text
MBR001|B001|2026-10-01|2026-10-08|2026-10-11|3000|1
```

## 🏗️ Class Overview
- **`LibraryItem`** — Abstract base class for library items.
- **`Book`** — Represents books, defines book late fees, and handles book serialization.
- **`Magazine`** — Represents magazines, defines magazine late fees, and handles magazine serialization.
- **`Member`** — Stores member information and handles member serialization.
- **`Loan`** — Stores loan transaction details.
- **`Library`** — Manages library items, members, transactions, text file operations, and menu navigation.

## 🚀 Getting Started

### Requirements
- A C++ compiler that supports C++11 or later.
- A terminal or command-line interface.
- GNU Compiler Collection (g++) or another compatible C++ compiler.

### 1. Compile the Program
Open a terminal in the project directory and run:

```bash
g++ -std=c++11 project.cpp -o ShelfMate
```

### 2. Run ShelfMate
**Windows:**

```powershell
.\ShelfMate.exe
```

**Linux or macOS:**

```bash
./ShelfMate
```

The TXT storage files will be created in the program's working directory when the application initializes or saves data.

## 🔑 Sample Accounts & Initial Data
The application provides default data on its first run when the storage files do not yet contain data.

### Login Accounts

| Role | Login ID | Name |
|---|---|---|
| Administrator | `ADMIN001` | Admin |
| Member | `MBR001` | Nida Nur Hafizhah |
| Member | `MBR002` | Regina Titian Pinasti |

### Default Items

| Item ID | Type | Title | Author / Issue |
|---|---|---|---|
| `B001` | Book | Clean Code | Robert C. Martin |
| `B002` | Book | The Pragmatic Programmer | Andrew Hunt |
| `M001` | Magazine | Tech Monthly | October 2026 |

## 🧪 Testing Late Fee Calculation & Data Persistence
Follow these steps to test borrowing, returning, late fee calculation, and permanent storage.
1. Run ShelfMate.
2. Log in as member `MBR001`.
3. Select **3. Borrow item** and enter item ID `B001`.
4. Choose `y` to use a simulated date and enter `2026-10-01`.
5. Close the program after the borrowing transaction succeeds.
6. Launch ShelfMate again.
7. Log in as member `MBR001`.
8. Select **4. Return item** and enter item ID `B001`.
9. Choose `y` to use a simulated date and enter `2026-10-11`.

### Expected Result
```text
Due date: 2026-10-08
Return date: 2026-10-11
Days overdue: 3
Late fee: Rp3000
```

**Expected outcome:** The borrowing record remains available after restarting the application, the item retains its borrowed status until returned, and the late fee is calculated based on the simulated return date.

## ⚠️ Limitations
- Terminal-based application without a graphical user interface (GUI).
- Authentication relies on member IDs without password verification.
- Data is stored in plain text files rather than a database.
- Storage files must remain accessible in the program's working directory.
