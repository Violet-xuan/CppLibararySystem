#include<iostream>
#include<string>
#pragma once
using namespace std;
class Book {
private:
    int bookID;
    string title;
    string author;
    bool isAvailable;
    int borrowedcount;
public:
    Book(int id=00000000, string t="Unknown", string a="Unknown") : bookID(id), title(t), author(a), isAvailable(true), borrowedcount(0) {}

    inline void updateStatus(bool status) {
        isAvailable = status;
    }
    inline void displayBookInfo() const {
        cout << "Book ID: " << bookID << ", Title: " << title << ", Author: " << author;
        cout << ", Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
    inline int getBookID() const {
        return bookID;
    }
    inline void setInfo(const string& t, const string& a) {
        title = t;
        author = a;
    }
    inline string getTitle() const {
        return title;
    }
    inline string getAuthor() const {
        return author;
    }
    bool getBookStatus(){
        return isAvailable;
    }
};