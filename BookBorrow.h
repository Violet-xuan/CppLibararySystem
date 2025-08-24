#include <iostream>
#include <string>
#include "Book.h"
#include "User.h"
#include <sstream>
#include <iomanip>
#include <chrono>
#include "FileHandle.h"
using namespace std;
#pragma once
string generateBorrowID(int &bookID, int &userID) {
    std::ostringstream oss;
    oss << std::setw(8) << std::setfill('0') << bookID
        << std::setw(8) << std::setfill('0') << userID;
    return oss.str();
}
long CurrentDate() {
    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);
    cout << "Current date and time: " << ctime(&now_c);
    return static_cast<int>(now_c);
}
long DateCauculate(string Date) {
    // Assuming Date is in the format "YYYY-MM-DD"
    int year, month, day;
    sscanf(Date.c_str(), "%d-%d-%d", &year, &month, &day);
    return (year)* 365 + month * 30 + day; // Convert to YYYYMMDD format
}
class BookBorrow: public Book, public User {
private:
    static int BorrowDuration;
    string borrowID;
    string borrowDate;
    string returnDate;
public:
    BookBorrow(int bID=0,int uID=0, string bDate=""){
        borrowID= generateBorrowID(bID, uID);
        borrowDate=bDate;
    }
    bool CauculateOverdue() {
        if(CurrentDate() - DateCauculate(borrowDate) > BorrowDuration) {
            return true;
        }
        return false;
    }
    string getBorrowDate() const{
        return borrowDate;
    }
    string getReturnDate() const {
        return returnDate;
    }
    string getBorrowID() const {
        return borrowID;
    }
    void displayBorrowInfo() const {
        cout << "Borrow ID: " << borrowID << ", Borrow Date: " << borrowDate;
        cout << ", Return Date: " << returnDate << endl;
        Book::displayBookInfo();
        User::displayUserInfo();
    }

};
int BookBorrow::BorrowDuration = 100;