#include<string.h>
#include<iostream>
using namespace std;
#pragma once
class User{
private:
    int userID;
    string name;
    string emailaddress;
    int borrowedBooksID[10];
    int borrowedCount;
public:
    User(int id=00000000, string n="Unknown", string email="Unknown") : userID(id), name(n), emailaddress(email), borrowedCount(0) {
        memset(borrowedBooksID, 0, sizeof(borrowedBooksID));
    }

    void borrowBook(int bookID) {
        if (borrowedCount < 10) {
            borrowedBooksID[borrowedCount++] = bookID;
        } else {
            cout << "Cannot borrow more than 10 books." << endl;
        }
    }
    int getUserID() const {
        return userID;
    }
    void returnBook(int bookID) {
        for (int i = 0; i < borrowedCount; i++) {
            if (borrowedBooksID[i] == bookID) {
                borrowedBooksID[i] = borrowedBooksID[--borrowedCount];
                return;
            }
        }
        cout << "Book not found in borrowed list." << endl;
    }
    void setInfo(const string& n, const string& email) {
        name = n;
        emailaddress = email;
    }
    void displayUserInfo() const {
        cout << "User ID: " << userID << ", Name: " << name << ", Email: " << emailaddress << endl;
        cout << "Borrowed Books: ";
        for (int i = 0; i < borrowedCount; i++) {
            cout << borrowedBooksID[i] << " ";
        }
        cout << endl;
    }
    int getBorrowedCount(){
        return borrowedCount; 
    }
};  