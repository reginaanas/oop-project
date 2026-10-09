#include <iostream>
#include <string>
#include <vector>
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
        virtual int calculateLateFee(int lateDay) const = 0;

        virtual ~LibraryItem() = default;
}
