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

        virtual ~LibraryItem() = default;

        class Book : public LibraryItem {
            private:
                string author;
            
            public:
                Book(string itemISBN, string itemTitle, string itemAuthor)
                    : LibraryItem(itemISBN, itemTitle), author(itemAuthor) {}
            
            string getType() const override {
                return "Book";
            }

            void displayInfo() const override {
                cout << "Type: " << getType() << endl;
                cout << "ISBN: " << getISBN() << endl;
                cout << "Title: " << getTitle() << endl;
                cout << "Author: " << author << endl;
                cout << "Status: " << (isBorrowed() ? "Borrowed" : "Available") << endl;
            }

            void calculateLateFee(int lateDays) const override {
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
                Magazine(string itemISBN, string itemTitle, string itemMonth)
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
        void
    }
}