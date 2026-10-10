#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <limits>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <fstream>

using namespace std;

// =====================================================
// HELPER FUNCTIONS FOR FILE HANDLING & ESCAPING
// =====================================================

// Mengganti delimiter '|' dengan '\|' agar aman disimpan ke file TXT
string escapePipe(const string &str)
{
    string result;
    for (char c : str)
    {
        if (c == '|')
            result += "\\|";
        else
            result += c;
    }
    return result;
}

// Mengembalikan karakter '|' yang di-escape
string unescapePipe(const string &str)
{
    string result;
    for (size_t i = 0; i < str.length(); ++i)
    {
        if (str[i] == '\\' && i + 1 < str.length() && str[i + 1] == '|')
        {
            result += '|';
            i++;
        }
        else
        {
            result += str[i];
        }
    }
    return result;
}

// Memisahkan string berdasarkan delimiter '|' dengan memperhatikan escape '\'
vector<string> splitFormattedLine(const string &line)
{
    vector<string> tokens;
    string currentToken;
    bool escaped = false;

    for (size_t i = 0; i < line.length(); ++i)
    {
        char c = line[i];
        if (escaped)
        {
            currentToken += c;
            escaped = false;
        }
        else if (c == '\\')
        {
            currentToken += c;
            escaped = true;
        }
        else if (c == '|')
        {
            tokens.push_back(unescapePipe(currentToken));
            currentToken.clear();
        }
        else
        {
            currentToken += c;
        }
    }
    tokens.push_back(unescapePipe(currentToken));
    return tokens;
}

// =====================================================
// DATE FUNCTIONS
// =====================================================

string getCurrentDate()
{
    time_t now = time(nullptr);
    tm *localInfo = localtime(&now);

    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localInfo);

    return string(buffer);
}

bool parseDate(const string &date, tm &dateInfo)
{
    if (date.length() != 10 ||
        date[4] != '-' ||
        date[7] != '-')
    {
        return false;
    }

    for (int i = 0; i < 10; i++)
    {
        if (i != 4 && i != 7 &&
            !isdigit(static_cast<unsigned char>(date[i])))
        {
            return false;
        }
    }

    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));

    dateInfo = {};
    dateInfo.tm_year = year - 1900;
    dateInfo.tm_mon = month - 1;
    dateInfo.tm_mday = day;
    dateInfo.tm_hour = 12;
    dateInfo.tm_isdst = -1;

    tm original = dateInfo;
    time_t value = mktime(&dateInfo);

    if (value == -1)
    {
        return false;
    }

    tm *checkedInfo = localtime(&value);

    if (checkedInfo == nullptr)
    {
        return false;
    }

    return checkedInfo->tm_year == original.tm_year &&
           checkedInfo->tm_mon == original.tm_mon &&
           checkedInfo->tm_mday == original.tm_mday;
}

time_t convertToTime(const string &date)
{
    tm dateInfo = {};

    if (!parseDate(date, dateInfo))
    {
        return static_cast<time_t>(-1);
    }

    return mktime(&dateInfo);
}

string addDays(const string &date, int days)
{
    time_t timeValue = convertToTime(date);

    if (timeValue == static_cast<time_t>(-1))
    {
        return "";
    }

    tm *info = localtime(&timeValue);

    if (info == nullptr)
    {
        return "";
    }

    tm adjustedTime = *info;
    adjustedTime.tm_mday += days;
    adjustedTime.tm_isdst = -1;

    if (mktime(&adjustedTime) == static_cast<time_t>(-1))
    {
        return "";
    }

    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &adjustedTime);

    return string(buffer);
}

// Returns the number of days from startDate to endDate.
int daysBetween(const string &startDate, const string &endDate)
{
    time_t start = convertToTime(startDate);
    time_t end = convertToTime(endDate);

    if (start == static_cast<time_t>(-1) ||
        end == static_cast<time_t>(-1))
    {
        return 0;
    }

    double difference = difftime(end, start);

    return static_cast<int>(difference / 86400.0);
}

// This function allows real dates or simulated dates.
string getDateForTransaction()
{
    char choice;

    while (true)
    {
        cout << "Use simulated date? (y/n): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 'y' || choice == 'Y')
        {
            string simulatedDate;

            while (true)
            {
                cout << "Enter date (YYYY-MM-DD): ";
                getline(cin, simulatedDate);

                tm dateInfo = {};

                if (parseDate(simulatedDate, dateInfo))
                {
                    return simulatedDate;
                }

                cout << "Invalid date. Please use YYYY-MM-DD.\n";
            }
        }

        if (choice == 'n' || choice == 'N')
        {
            return getCurrentDate();
        }

        cout << "Please enter y or n.\n";
    }
}

// Input Functions
void printLine()
{
    cout << "---------------------------------------------\n";
}

string readText(const string &prompt)
{
    string value;

    cout << prompt;
    getline(cin, value);

    return value;
}

int readInteger(const string &prompt)
{
    int value;

    while (true)
    {
        cout << prompt;

        if (cin >> value)
        {
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Invalid input. Please enter a number.\n";

        cin.clear();
        cin.ignore(
            numeric_limits<streamsize>::max(), '\n');
    }
}

// Base Class: Library Item
class LibraryItem
{
private:
    string id;
    string title;
    bool borrowed;
    string borrowerID;

public:
    LibraryItem(string itemID, string itemTitle)
        : id(itemID),
          title(itemTitle),
          borrowed(false),
          borrowerID("") {}

    virtual ~LibraryItem() = default;

    string getID() const
    {
        return id;
    }

    string getTitle() const
    {
        return title;
    }

    bool isBorrowed() const
    {
        return borrowed;
    }

    string getBorrowerID() const
    {
        return borrowerID;
    }

    void borrowItem(const string &memberID)
    {
        borrowed = true;
        borrowerID = memberID;
    }

    void returnItem()
    {
        borrowed = false;
        borrowerID = "";
    }

    virtual string getType() const = 0;

    virtual void displayInfo() const = 0;

    virtual int calculateLateFee(int lateDays) const = 0;

    virtual string serialize() const = 0;
};

// Derived Class: Book
class Book : public LibraryItem
{
private:
    string author;

public:
    Book(string itemID, string title, string itemAuthor)
        : LibraryItem(itemID, title),
          author(itemAuthor) {}

    string getAuthor() const
    {
        return author;
    }

    string getType() const override
    {
        return "Book";
    }

    void displayInfo() const override
    {
        cout << "ID: " << getID()
             << " | Type: Book"
             << " | Title: " << getTitle()
             << " | Author: " << author
             << " | Status: "
             << (isBorrowed() ? "Borrowed" : "Available")
             << '\n';
    }

    int calculateLateFee(int lateDays) const override
    {
        return lateDays > 0 ? lateDays * 1000 : 0;
    }

    string serialize() const override
    {
        // Format: Book|ID|Title|Author|isBorrowed|borrowerID
        return "Book|" + escapePipe(getID()) + "|" + escapePipe(getTitle()) + "|" +
               escapePipe(author) + "|" + (isBorrowed() ? "1" : "0") + "|" +
               escapePipe(getBorrowerID());
    }
};

// Derived Class: Magazine
class Magazine : public LibraryItem
{
private:
    string issue;

public:
    Magazine(string itemID, string title, string magazineIssue)
        : LibraryItem(itemID, title),
          issue(magazineIssue) {}

    string getIssue() const
    {
        return issue;
    }

    string getType() const override
    {
        return "Magazine";
    }

    void displayInfo() const override
    {
        cout << "ID: " << getID()
             << " | Type: Magazine"
             << " | Title: " << getTitle()
             << " | Issue: " << issue
             << " | Status: "
             << (isBorrowed() ? "Borrowed" : "Available")
             << '\n';
    }

    int calculateLateFee(int lateDays) const override
    {
        return lateDays > 0 ? lateDays * 500 : 0;
    }

    string serialize() const override
    {
        // Format: Magazine|ID|Title|Issue|isBorrowed|borrowerID
        return "Magazine|" + escapePipe(getID()) + "|" + escapePipe(getTitle()) + "|" +
               escapePipe(issue) + "|" + (isBorrowed() ? "1" : "0") + "|" +
               escapePipe(getBorrowerID());
    }
};

// Member Class
class Member
{
private:
    string id;
    string name;

public:
    Member(string memberID, string memberName)
        : id(memberID), name(memberName) {}

    string getID() const
    {
        return id;
    }

    string getName() const
    {
        return name;
    }

    void displayInfo() const
    {
        cout << "ID: " << id
             << " | Name: " << name << '\n';
    }

    string serialize() const
    {
        // Format: ID|Name
        return escapePipe(id) + "|" + escapePipe(name);
    }
};

// Loan Class
class Loan
{
private:
    string memberID;
    string itemID;
    string borrowDate;
    string dueDate;
    string returnDate;
    int fine;
    bool returned;

public:
    Loan(string member, string item,
         string borrowedOn, string due)
        : memberID(member),
          itemID(item),
          borrowDate(borrowedOn),
          dueDate(due),
          returnDate("-"),
          fine(0),
          returned(false) {}

    Loan(string member, string item, string borrowedOn,
         string due, string retDate, int fee, bool isRet)
        : memberID(member),
          itemID(item),
          borrowDate(borrowedOn),
          dueDate(due),
          returnDate(retDate),
          fine(fee),
          returned(isRet) {}

    string getMemberID() const
    {
        return memberID;
    }

    string getItemID() const
    {
        return itemID;
    }

    string getDueDate() const
    {
        return dueDate;
    }

    bool isReturned() const
    {
        return returned;
    }

    void completeReturn(string date, int fee)
    {
        returnDate = date;
        fine = fee;
        returned = true;
    }

    void displayInfo() const
    {
        cout << "Member: " << memberID
             << " | Item: " << itemID
             << " | Borrowed: " << borrowDate
             << " | Due: " << dueDate
             << " | Returned: " << returnDate
             << " | Fine: Rp" << fine
             << " | Status: "
             << (returned ? "Returned" : "Active")
             << '\n';
    }

    string serialize() const
    {
        // Format: MemberID|ItemID|BorrowDate|DueDate|ReturnDate|Fine|Returned
        return escapePipe(memberID) + "|" + escapePipe(itemID) + "|" +
               escapePipe(borrowDate) + "|" + escapePipe(dueDate) + "|" +
               escapePipe(returnDate) + "|" + to_string(fine) + "|" +
               (returned ? "1" : "0");
    }
};

// Library Class
class Library
{
private:
    vector<LibraryItem *> items;
    vector<Member> members;
    vector<Loan> loans;

    int nextBookNumber = 1;
    int nextMagazineNumber = 1;
    int nextMemberNumber = 1;

    const string itemsFile = "items.txt";
    const string membersFile = "members.txt";
    const string loansFile = "loans.txt";

    // File I/O Methods
    void saveItems() const
    {
        ofstream outFile(itemsFile);
        if (!outFile.is_open())
            return;

        for (const LibraryItem *item : items)
        {
            outFile << item->serialize() << "\n";
        }
    }

    void saveMembers() const
    {
        ofstream outFile(membersFile);
        if (!outFile.is_open())
            return;

        for (const Member &member : members)
        {
            outFile << member.serialize() << "\n";
        }
    }

    void saveLoans() const
    {
        ofstream outFile(loansFile);
        if (!outFile.is_open())
            return;

        for (const Loan &loan : loans)
        {
            outFile << loan.serialize() << "\n";
        }
    }

    void loadItems()
    {
        ifstream inFile(itemsFile);
        if (!inFile.is_open())
            return;

        string line;
        while (getline(inFile, line))
        {
            if (line.empty())
                continue;

            vector<string> tokens = splitFormattedLine(line);
            if (tokens.size() < 6)
                continue;

            string type = tokens[0];
            string id = tokens[1];
            string title = tokens[2];
            string detail = tokens[3];
            bool isBorrowed = (tokens[4] == "1");
            string borrowerID = tokens[5];

            LibraryItem *item = nullptr;
            if (type == "Book")
            {
                item = new Book(id, title, detail);

                if (id.length() >= 2 && id[0] == 'B')
                {
                    try
                    {
                        int num = stoi(id.substr(1));
                        if (num >= nextBookNumber)
                            nextBookNumber = num + 1;
                    }
                    catch (...)
                    {
                    }
                }
            }
            else if (type == "Magazine")
            {
                item = new Magazine(id, title, detail);

                if (id.length() >= 2 && id[0] == 'M')
                {
                    try
                    {
                        int num = stoi(id.substr(1));
                        if (num >= nextMagazineNumber)
                            nextMagazineNumber = num + 1;
                    }
                    catch (...)
                    {
                    }
                }
            }

            if (item != nullptr)
            {
                if (isBorrowed)
                {
                    item->borrowItem(borrowerID);
                }
                items.push_back(item);
            }
        }
    }

    void loadMembers()
    {
        ifstream inFile(membersFile);
        if (!inFile.is_open())
            return;

        string line;
        while (getline(inFile, line))
        {
            if (line.empty())
                continue;

            vector<string> tokens = splitFormattedLine(line);
            if (tokens.size() < 2)
                continue;

            string id = tokens[0];
            string name = tokens[1];

            members.emplace_back(id, name);

            if (id.length() >= 4 && id.substr(0, 3) == "MBR")
            {
                try
                {
                    int num = stoi(id.substr(3));
                    if (num >= nextMemberNumber)
                        nextMemberNumber = num + 1;
                }
                catch (...)
                {
                }
            }
        }
    }

    void loadLoans()
    {
        ifstream inFile(loansFile);
        if (!inFile.is_open())
            return;

        string line;
        while (getline(inFile, line))
        {
            if (line.empty())
                continue;

            vector<string> tokens = splitFormattedLine(line);
            if (tokens.size() < 7)
                continue;

            string memberID = tokens[0];
            string itemID = tokens[1];
            string borrowDate = tokens[2];
            string dueDate = tokens[3];
            string returnDate = tokens[4];
            int fine = stoi(tokens[5]);
            bool returned = (tokens[6] == "1");

            loans.emplace_back(memberID, itemID, borrowDate, dueDate, returnDate, fine, returned);
        }
    }

    void loadDataOrSeedDefault()
    {
        ifstream fItems(itemsFile);
        ifstream fMembers(membersFile);
        ifstream fLoans(loansFile);

        bool hasItems = fItems.good();
        bool hasMembers = fMembers.good();
        bool hasLoans = fLoans.good();

        fItems.close();
        fMembers.close();
        fLoans.close();

        if (!hasItems || !hasMembers || !hasLoans)
        {
            // Sample collection
            items.push_back(new Book("B001", "Clean Code", "Robert C. Martin"));
            items.push_back(new Book("B002", "The Pragmatic Programmer", "Andrew Hunt"));
            items.push_back(new Magazine("M001", "Tech Monthly", "October 2026"));

            // Sample members
            members.emplace_back("MBR001", "Nida Nur Hafizhah");
            members.emplace_back("MBR002", "Regina Titian Pinasti");

            nextBookNumber = 3;
            nextMagazineNumber = 2;
            nextMemberNumber = 3;

            saveItems();
            saveMembers();
            saveLoans();
        }
        else
        {
            loadItems();
            loadMembers();
            loadLoans();
        }
    }

    // Search and Helper
    LibraryItem *findItem(const string &itemID)
    {
        for (LibraryItem *item : items)
        {
            if (item->getID() == itemID)
            {
                return item;
            }
        }

        return nullptr;
    }

    Member *findMember(const string &memberID)
    {
        for (Member &member : members)
        {
            if (member.getID() == memberID)
            {
                return &member;
            }
        }

        return nullptr;
    }

    void displayItems() const
    {
        printLine();
        cout << "LIBRARY COLLECTION\n";
        printLine();

        if (items.empty())
        {
            cout << "No items available.\n";
            return;
        }

        for (const LibraryItem *item : items)
        {
            item->displayInfo();
        }
    }

    void searchItems() const
    {
        string keyword = readText("Enter title keyword: ");
        bool found = false;

        for (const LibraryItem *item : items)
        {
            string title = item->getTitle();
            string searchKeyword = keyword;

            for (char &c : title)
            {
                c = static_cast<char>(
                    tolower(static_cast<unsigned char>(c)));
            }

            for (char &c : searchKeyword)
            {
                c = static_cast<char>(
                    tolower(static_cast<unsigned char>(c)));
            }

            if (title.find(searchKeyword) != string::npos)
            {
                item->displayInfo();
                found = true;
            }
        }

        if (!found)
        {
            cout << "No matching item found.\n";
        }
    }

    void addBook()
    {
        string title = readText("Enter book title: ");
        string author = readText("Enter author: ");

        string id = "B";

        if (nextBookNumber < 10)
        {
            id += "00";
        }
        else if (nextBookNumber < 100)
        {
            id += "0";
        }

        id += to_string(nextBookNumber);
        nextBookNumber++;

        items.push_back(new Book(id, title, author));
        saveItems();

        cout << "Book added successfully. ID: "
             << id << '\n';
    }

    void addMagazine()
    {
        string title = readText("Enter magazine title: ");
        string issue = readText("Enter magazine issue: ");

        string id = "M";

        if (nextMagazineNumber < 10)
        {
            id += "00";
        }
        else if (nextMagazineNumber < 100)
        {
            id += "0";
        }

        id += to_string(nextMagazineNumber);
        nextMagazineNumber++;

        items.push_back(new Magazine(id, title, issue));
        saveItems();

        cout << "Magazine added successfully. ID: "
             << id << '\n';
    }

    void registerMember()
    {
        string name = readText("Enter member name: ");

        string id = "MBR";

        if (nextMemberNumber < 10)
        {
            id += "00";
        }
        else if (nextMemberNumber < 100)
        {
            id += "0";
        }

        id += to_string(nextMemberNumber);
        nextMemberNumber++;

        members.emplace_back(id, name);
        saveMembers();

        cout << "Member registered successfully. ID: "
             << id << '\n';
    }

    void displayMembers() const
    {
        printLine();
        cout << "REGISTERED MEMBERS\n";
        printLine();

        for (const Member &member : members)
        {
            member.displayInfo();
        }
    }

    void displayAllTransactions() const
    {
        printLine();
        cout << "ALL TRANSACTIONS\n";
        printLine();

        if (loans.empty())
        {
            cout << "No transactions recorded.\n";
            return;
        }

        for (const Loan &loan : loans)
        {
            loan.displayInfo();
        }
    }

    void borrowItem(const string &memberID)
    {
        string itemID = readText("Enter item ID to borrow: ");

        LibraryItem *item = findItem(itemID);

        if (item == nullptr)
        {
            cout << "Item not found.\n";
            return;
        }

        if (item->isBorrowed())
        {
            cout << "This item is already borrowed.\n";
            return;
        }

        string today = getDateForTransaction();
        string dueDate = addDays(today, 7);

        if (dueDate.empty())
        {
            cout << "Could not calculate the due date.\n";
            return;
        }

        item->borrowItem(memberID);

        loans.emplace_back(
            memberID, itemID, today, dueDate);

        saveItems();
        saveLoans();

        cout << "\nBorrowing successful!\n";
        cout << "Item: " << item->getTitle() << '\n';
        cout << "Borrow date: " << today << '\n';
        cout << "Due date: " << dueDate << '\n';
        cout << "Loan duration: 7 days\n";
    }

    void returnItem(const string &memberID)
    {
        string itemID = readText("Enter item ID to return: ");

        LibraryItem *item = findItem(itemID);

        if (item == nullptr)
        {
            cout << "Item not found.\n";
            return;
        }

        if (!item->isBorrowed())
        {
            cout << "This item is not currently borrowed.\n";
            return;
        }

        if (item->getBorrowerID() != memberID)
        {
            cout << "You cannot return another member's item.\n";
            return;
        }

        int loanIndex = -1;

        for (int i = static_cast<int>(loans.size()) - 1;
             i >= 0; i--)
        {
            if (loans[i].getItemID() == itemID &&
                loans[i].getMemberID() == memberID &&
                !loans[i].isReturned())
            {
                loanIndex = i;
                break;
            }
        }

        if (loanIndex == -1)
        {
            cout << "Active loan record not found.\n";
            return;
        }

        string returnDate = getDateForTransaction();

        int lateDays = daysBetween(
            loans[loanIndex].getDueDate(),
            returnDate);

        if (lateDays < 0)
        {
            lateDays = 0;
        }

        // Polymorphism: Book and Magazine use different fee rates.
        int fee = item->calculateLateFee(lateDays);

        loans[loanIndex].completeReturn(returnDate, fee);
        item->returnItem();

        saveItems();
        saveLoans();

        cout << "\nReturn successful!\n";
        cout << "Item: " << item->getTitle() << '\n';
        cout << "Due date: "
             << loans[loanIndex].getDueDate() << '\n';
        cout << "Return date: " << returnDate << '\n';
        cout << "Days overdue: " << lateDays << '\n';
        cout << "Late fee: Rp" << fee << '\n';
    }

    void displayMemberTransactions(const string &memberID) const
    {
        printLine();
        cout << "YOUR TRANSACTION HISTORY\n";
        printLine();

        bool found = false;

        for (const Loan &loan : loans)
        {
            if (loan.getMemberID() == memberID)
            {
                loan.displayInfo();
                found = true;
            }
        }

        if (!found)
        {
            cout << "You have no transactions yet.\n";
        }
    }

    void adminMenu()
    {
        int choice;

        do
        {
            printLine();
            cout << "SHELFMATE - ADMIN MENU\n";
            printLine();
            cout << "1. View all items\n";
            cout << "2. Search items\n";
            cout << "3. Add book\n";
            cout << "4. Add magazine\n";
            cout << "5. Register member\n";
            cout << "6. View all members\n";
            cout << "7. View all transactions\n";
            cout << "0. Logout\n";

            choice = readInteger("Choose menu: ");

            switch (choice)
            {
            case 1:
                displayItems();
                break;
            case 2:
                searchItems();
                break;
            case 3:
                addBook();
                break;
            case 4:
                addMagazine();
                break;
            case 5:
                registerMember();
                break;
            case 6:
                displayMembers();
                break;
            case 7:
                displayAllTransactions();
                break;
            case 0:
                cout << "Admin logged out.\n";
                break;
            default:
                cout << "Invalid menu choice.\n";
            }
        } while (choice != 0);
    }

    void memberMenu(const Member &member)
    {
        int choice;
        string memberID = member.getID();

        do
        {
            printLine();
            cout << "SHELFMATE - MEMBER MENU\n";
            cout << "Welcome, " << member.getName() << "!\n";
            printLine();
            cout << "1. View all items\n";
            cout << "2. Search items\n";
            cout << "3. Borrow item\n";
            cout << "4. Return item\n";
            cout << "5. View my transaction history\n";
            cout << "0. Logout\n";

            choice = readInteger("Choose menu: ");

            switch (choice)
            {
            case 1:
                displayItems();
                break;
            case 2:
                searchItems();
                break;
            case 3:
                borrowItem(memberID);
                break;
            case 4:
                returnItem(memberID);
                break;
            case 5:
                displayMemberTransactions(memberID);
                break;
            case 0:
                cout << "Member logged out.\n";
                break;
            default:
                cout << "Invalid menu choice.\n";
            }
        } while (choice != 0);
    }

public:
    Library()
    {
        loadDataOrSeedDefault();
    }

    ~Library()
    {
        for (LibraryItem *item : items)
        {
            delete item;
        }
    }

    void run()
    {
        int choice;

        do
        {
            printLine();
            cout << "WELCOME TO SHELFMATE\n";
            printLine();
            cout << "1. Login\n";
            cout << "0. Exit\n";

            choice = readInteger("Choose menu: ");

            if (choice == 1)
            {
                string id = readText("Enter your ID: ");

                if (id == "ADMIN001")
                {
                    adminMenu();
                }
                else
                {
                    Member *member = findMember(id);

                    if (member != nullptr)
                    {
                        memberMenu(*member);
                    }
                    else
                    {
                        cout << "ID not found. Login failed.\n";
                    }
                }
            }
            else if (choice == 0)
            {
                cout << "Thank you for using ShelfMate!\n";
            }
            else
            {
                cout << "Invalid menu choice.\n";
            }
        } while (choice != 0);
    }
};

// Main Function
int main()
{
    Library shelfMate;
    shelfMate.run();

    return 0;
}