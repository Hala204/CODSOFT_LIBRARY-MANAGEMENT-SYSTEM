#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Book 
{
public:
    int id;
    string title;
    string author;
    string isbn;
    bool isAvailable;

    Book(int id, string title, string author, string isbn)
        : id(id), title(title), author(author), isbn(isbn), isAvailable(true) {}
};

class Borrower
{
public:
    int id;
    string name;
    string email;
    string phone;

    Borrower(int id, string name, string email, string phone)
        : id(id), name(name), email(email), phone(phone) {}
};

class Transaction
{
public:
    int transactionId;
    int bookId;
    int borrowerId;
    time_t checkoutDate;
    time_t dueDate;
    time_t returnDate;
    double fineAmount;

    Transaction(int transactionId, int bookId, int borrowerId, time_t checkoutDate, time_t dueDate)
        : transactionId(transactionId), bookId(bookId), borrowerId(borrowerId),
        checkoutDate(checkoutDate), dueDate(dueDate), returnDate(0), fineAmount(0) {}
};

class Library 
{
private:
    vector<Book> books;
    vector<Borrower> borrowers;
    vector<Transaction> transactions;
    int nextBookId;
    int nextBorrowerId;
    int nextTransactionId;

public:
    Library() : nextBookId(1), nextBorrowerId(1), nextTransactionId(1) {}

    void addBook(string title, string author, string isbn)
    {
        books.push_back(Book(nextBookId++, title, author, isbn));
        cout << "Book added successfully";
        cout << endl;
    }

    void addBorrower(string name, string email, string phone) 
    {
        borrowers.push_back(Borrower(nextBorrowerId++, name, email, phone));
        cout << "Borrower added successfully";
        cout << endl;
    }

    void checkoutBook(int bookId, int borrowerId) 
    {
        for (Book& book : books) 
        {
            if (book.id == bookId) 
            {
                if (book.isAvailable) 
                {
                    book.isAvailable = false;
                    time_t now = time(0);
                    time_t due = now + 14 * 24 * 60 * 60; 
                    transactions.push_back(Transaction(nextTransactionId++, bookId, borrowerId, now, due));
                    cout << "Book checked out successfully";
                    cout << endl;
                    return;
                }
                else 
                {
                    cout << "Book is not available"; 
                    cout << endl;
                    return;
                }
            }
        }
        cout << "Book not found";
        cout << endl;
    }

    void returnBook(int bookId) 
    {
        for (Transaction& transaction : transactions)
        {
            if (transaction.bookId == bookId && transaction.returnDate == 0) 
            {
                transaction.returnDate = time(0);
                time_t now = time(0);
                if (now > transaction.dueDate) 
                {
                    transaction.fineAmount = difftime(now, transaction.dueDate) / (24 * 60 * 60) * 1; 
                }
                for (Book& book : books) 
                {
                    if (book.id == bookId) 
                    {
                        book.isAvailable = true;
                        break;
                    }
                }
                cout << "Book returned successfully";
                cout << endl;
                if (transaction.fineAmount > 0) {
                    cout << "Fine amount: $" << transaction.fineAmount;
                    cout << endl;
                }
                return;
            }
        }
        cout << "Transaction not found";
        cout << endl;
    }

    void searchBook(string query) 
    {
        for (const Book& book : books) 
        {
            if (book.title.find(query) != string::npos || book.author.find(query) != string::npos || book.isbn.find(query) != string::npos) 
            {
                cout << "Book ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author << ", ISBN: " << book.isbn << ", Available: " << (book.isAvailable ? "Yes" : "No");
                cout << endl;
            }
        }
    }
};


void displayMenu() 
{
    cout << "Library Management System\n";
    cout << "1. Add Book\n";
    cout << "2. Add Borrower\n";
    cout << "3. Checkout Book\n";
    cout << "4. Return Book\n";
    cout << "5. Search Book\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    Library library;
    int choice;

    do 
    {
        displayMenu();
        cin >> choice;

        switch (choice) 
        {
        case 1: 
        {
            string title, author, isbn;
            cout << "Enter title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter author: ";
            getline(cin, author);
            cout << "Enter ISBN: ";
            getline(cin, isbn);
            library.addBook(title, author, isbn);
            break;
        }
        case 2: 
        {
            string name, email, phone;
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter email: ";
            getline(cin, email);
            cout << "Enter phone: ";
            getline(cin, phone);
            library.addBorrower(name, email, phone);
            break;
        }
        case 3: 
        {
            int bookId, borrowerId;
            cout << "Enter book ID: ";
            cin >> bookId;
            cout << "Enter borrower ID: ";
            cin >> borrowerId;
            library.checkoutBook(bookId, borrowerId);
            break;
        }
        case 4:
        {
            int bookId;
            cout << "Enter book ID: ";
            cin >> bookId;
            library.returnBook(bookId);
            break;
        }
        case 5: 
        {
            string query;
            cout << "Enter search query (title/author/ISBN): ";
            cin.ignore();
            getline(cin, query);
            library.searchBook(query);
            break;
        }
        case 6:
            cout << "Exiting the system";
            cout << endl;
            break;
        default:
            cout << "Invalid choice. Please try again";
            cout << endl;
            break;
        }
    } 
    while (choice != 6);
}
