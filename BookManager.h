#include <vector>
#include <algorithm>
#include <string> 
#include "Book.h"
#include "FileHandle.h" 
#include<fstream>
fstream BookFile("BookData.txt",ios::app);
class BookManager {
private:
    vector<Book> books;
public:
    BookManager(){
        ifstream InBookFile("BookData.txt");
        if(!InBookFile){
            cerr<<"Cannot open BookDataFile"<<endl;
            return ;
        }
        int bid;
        string TMPtitle,TMPauthor;
        while(InBookFile>>bid>>TMPtitle>>TMPauthor){
            books.push_back(Book(bid,TMPtitle,TMPauthor));
        }
        InBookFile.close();
    }
    void addBook(const Book& book) { 
        books.push_back(book);
        BookFile<<book.getBookID()<<" "<<book.getTitle()<<" "<<book.getAuthor()<<endl; 
    }
    bool deleteBook(const int& bookID) {
        auto it = remove_if(books.begin(), books.end(), [&](const Book& b){ return b.getBookID() == bookID; });
        if (it != books.end()) {
            books.erase(it, books.end());
            removeIdFromFile("BookData.txt",bookID);
            return true;
        }
        return false;
    }
    Book* findBook(const int & bookID) {
        for (auto& book : books) {
            if (book.getBookID() == bookID) return &book;
        }
        return nullptr;
    }
    void modifyBook(const int& bookID, const string& title, const string& author) {
        Book* book = findBook(bookID);
        if (book) book->setInfo(title, author);
    }
    // 模糊查询
    void fuzzySearch(const string& keyword) {
        for (const auto& book : books) {
            if (book.getTitle().find(keyword) != string::npos ||
                book.getAuthor().find(keyword) != string::npos) {
                book.displayBookInfo();
            }
        }
    }
    void listBooks() {
        for (const auto& book : books) book.displayBookInfo();
    }
    void bookSearchPage() {
        cout << "Book Search Page" << endl;
        cout << "1. Search by Title" << endl;
        cout << "2. Search by Author" << endl;
        cout << "3. Return to Main Menu" << endl;
        cout << "Please select an option (1-3): ";
        int choice;
        cin >> choice;  
        switch(choice) {
            case 1: {
                string title;
                cout << "Enter Title to search: ";
                cin.ignore();
                getline(cin, title);
                fuzzySearch(title);
                break;
            }
            case 2: {
                string author;
                cout << "Enter Author to search: ";
                cin.ignore();
                getline(cin, author);
                fuzzySearch(author);
                break;
            }
            case 3:
                return; // 返回主菜单
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }
    void bookManagementPage() {
        cout << "Book Management Page" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Delete Book" << endl;
        cout << "3. Modify Book" << endl;
        cout << "4. List Books" << endl;
        cout << "5. Return to Main Menu" << endl;
        cout << "Please select an option (1-5): ";
        int choice;
        cin >> choice;
        switch(choice){
            case 1: {
                int id;
                string title, author;
                cout << "Enter Book ID: ";
                cin >> id;
                cout << "Enter Title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter Author: ";
                getline(cin, author);
                addBook(Book(id, title, author));
                break;
            }
            case 2: {
                int id;
                cout << "Enter Book ID to delete: ";
                cin >> id;
                if (deleteBook(id)) {
                    cout << "Book deleted successfully." << endl;
                } else {
                    cout << "Book not found." << endl;
                }
                break;
            }
            case 3: {
                int id;
                string title, author;
                cout << "Enter Book ID to modify: ";
                cin >> id;
                cout << "Enter new Title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter new Author: ";
                getline(cin, author);
                modifyBook(id, title, author);
                break;
            }
            case 4:
                listBooks();
                break;
            case 5:
                return; // 返回主菜单
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }
};