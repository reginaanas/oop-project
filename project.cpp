#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

class LibraryItem {
private:
    string isbn;
    string title;
    bool borrowed;

public:
    LibraryItem(string itemISBN, string itemTitle)
        : isbn(itemISBN), title(itemTitle), borrowed(false) {}

    virtual ~LibraryItem() = default;

    string getISBN() const {
        return isbn;
    }

    string getTitle() const {
        return title;
    }

    bool isBorrowed() const {
        return borrowed;
    }

    bool borrowItem() {
        if (borrowed) {
            return false;
        }

        borrowed = true;
        return true;
    }

    bool returnItem() {
        if(!borrowed) {
            return false;
        }

        borrowed = false;
        return true;
    }

    virtual string getType() const = 0;
    virtual void displayInfo() const = 0;
    virtual int calculateLateFee(int lateDays) const = 0;
};
        

class Book : public LibraryItem {
private:
    string author;
            
public:
    Book(const string& itemISBN, const string& itemTitle, const string& itemAuthor)
        : LibraryItem(itemISBN, itemTitle), author(itemAuthor) {}
            
    string getType() const override {
        return "Book";
        }

    void displayInfo() const override {
        cout << "Type   : " << getType() << endl;
        cout << "ISBN   : " << getISBN() << endl;
        cout << "Title  : " << getTitle() << endl;
        cout << "Author : " << author << endl;
        cout << "Status : " << (isBorrowed() ? "Borrowed" : "Available") << endl;
    }

    int calculateLateFee(int lateDays) const override {
        if (lateDays <= 0){
            return 0;
        }
        return lateDays * 1000;
    }
};

class Magazine : public LibraryItem {
private:
    string publicationMonth;
            
public:
    Magazine(const string& itemISBN, const string& itemTitle, const string& itemMonth)
        : LibraryItem(itemISBN, itemTitle), publicationMonth(itemMonth) {}
            
    string getType() const override {
        return "Magazine";
    }

    void display() const override {
        cout << "Type: " << getType() << endl;
        cout << "ISBN: " << getISBN() << endl;
        cout << "Title: " << getTitle() << endl;
        cout << "Publication Month: " << publicationMonth << endl;
        cout << "Status: " << (isBorrowed() ? "Borrowed" : "Available") << endl;
    }
            
    int calculateLateFee(int lateDays) const override {
        if(lateDays <= 0){
            return 0;
        }
        return lateDays * 500;
    }
};

class Library {
private:
    vector<LibraryItem*> items;
    
public: 
    // Add a new item to library
    void addItem(LibraryItem* item) {
        item.push_back(item);
    }

    // Display all items
    void displayItems() const {
        if(item.empty()) {
            cout << "No itemm available. \n";
            return;
        }
        for(LibraryItem* item : items) {
            item->displayInfo();
        }
    }

    // Find item by ISBN
    LibrayItem* findItem(const string& itemISBN) const {
    for(LibraryItem* item : items) {
            if(item->getISBN() == itemISBN) {
                return item;
            }
        }
        return nullptr;
    }

    // Search and display an item
    void searchItem(const string& itemISBN) const {
        LibraryItem* item = findItem(itemISBN);

        if(item == nullptr) {
            cout << "Item not found. \n";
        } else {
            item->displayInfo();
        }
    }

    // Borrow an item
    void borrowItem(const string& itemISBN) {
    LibraryItem* item = findItem(itemISBN);

    if (item == nullptr) {
        cout << "Item not found.\n";
        return;
    }

    if (item->borrowItem()) {
        cout << "Borrowing successful!\n";
    } else {
        cout << "This item is already borrowed.\n";
    }
}

// Return an item and calculate the late fee
void returnItem(const string& itemISBN, int lateDays) {
    if (lateDays < 0) {
        cout << "Late days cannot be negative.\n";
        return;
    }

    LibraryItem* item = findItem(itemISBN);

    if (item == nullptr) {
        cout << "Item not found.\n";
        return;
    }

    if (!item->returnItem()) {
        cout << "This item was not borrowed.\n";
        return;
    }

    int fee = item->calculateLateFee(lateDays);

    cout << "Returning successful!\n";
    cout << "Late fee: Rp" << fee << '\n';
    }
};

int readInteger(const string& prompt) {
    int value;

    while (true) {
        cout << prompt;

        if (cin >> value) {
            return value;
        }

        cout << "Invalid input. Please enter a number.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


int main() {
    // Create sample items
    Book book1("B001", "Clean Code", "Robert C. Martin");
    Book book2("B002", "The Pragmatic Programmer", "Andy Hunt");

    Magazine magazine1("M001", "Tech Monthly", "October 2026");

    // Create the library
    Library library;

    // Add items to the library
    library.addItem(&book1);
    library.addItem(&book2);
    library.addItem(&magazine1);

    int choice;
    string itemISBN;
    int lateDays;

    while (true) {
        cout << "\n===== MINI LIBRARY SYSTEM =====\n";
        cout << "1. Display all items\n";
        cout << "2. Search item by ID\n";
        cout << "3. Borrow an item\n";
        cout << "4. Return an item\n";
        cout << "5. Exit\n";

        choice = readInteger("Choose menu: ");

        if (choice == 1) {
            library.displayItems();
        }
        else if (choice == 2) {
            cout << "Enter item ISBN: ";
            cin >> itemISBN;

            library.searchItem(itemISBN);
        }
        else if (choice == 3) {
            cout << "Enter item ISBN: ";
            cin >> itemISBN;

            library.borrowItem(itemISBN);
        }
        else if (choice == 4) {
            cout << "Enter item ISBN: ";
            cin >> itemISBN;

            lateDays = readInteger("Enter late days (0 if on time): ");

            library.returnItem(itemISBN, lateDays);
        }
        else if (choice == 5) {
            cout << "Thank you for using the library system!\n";
            break;
        }
        else {
            cout << "Invalid menu choice. Please choose 1-5.\n";
        }
    }

    return 0;
}

