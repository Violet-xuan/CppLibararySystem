#include <vector>
#include <string>
#include "Book.h"
#include "User.h"
using namespace std;
#include "BookBorrow.h"
#include "FileHandle.h"
#pragma once
fstream RecordFile("RecordData.txt",ios::app);
class RecordManager {
private:
    vector<BookBorrow> records;
public:
    RecordManager(){
        ifstream InRecordFile("BookData.txt");
        if(!InRecordFile){
            cerr<<"Cannot open RecordFile"<<endl;
            return ;
        }
        int bid,uid;
        string TMPbdate;
        while(InRecordFile>>bid>>uid>>TMPbdate){
            records.push_back(BookBorrow(bid,uid,TMPbdate));
        }
        InRecordFile.close();
    }
    void addRecord(const BookBorrow& record) { 
        
        records.push_back(record); 
        RecordFile<<record.getBorrowID()<<" ";
        RecordFile<<record.getBorrowDate()<<endl;
    }
    void listRecords() {
        for (const auto& rec : records) {
            // 假设BookBorrow有display方法
            rec.displayBorrowInfo();
        }
    }
    // 查询某用户的借阅历史
    void userHistory(const int& userID) {
        for (const auto& rec : records) {
            if (rec.getUserID() == userID) rec.displayBorrowInfo();
        }
    }
    
    // 查询某图书的借阅历史
    void bookHistory(const int& bookID) {
        for (const auto& rec : records) {
            if (rec.getBookID() == bookID) rec.displayBorrowInfo();
        }
    }
    void returnBook(int bookID, int userID) {
        for (auto it = records.begin(); it != records.end(); ++it) {
            if (it->getBookID() == bookID && it->getUserID() == userID) {
                // 假设BookBorrow有一个方法来处理归还逻辑
                it->returnBook(bookID);
                records.erase(it);
                cout << "Book returned successfully!" << endl;
                return;
            }
        }
        cout << "Record not found." << endl;
    }
    void recordManagementPage() {
        cout << "Record Management Page" << endl;
        cout << "1. Add Record" << endl;
        cout << "2. List Records" << endl;
        cout << "3. User History" << endl;
        cout << "4. Book History" << endl;
        cout << "5. Return to Main Menu" << endl;
        cout << "Please select an option (1-5): ";
        int AdminChoice;
        cin>>AdminChoice;
        switch(AdminChoice){
            case 1:{
                cout<<"Please Enter the UserID"<<endl;
                int uid,bid;
                cin>>uid;
                cout<<"Please Enter the BookID"<<endl;
                cin>>bid;
                string bdate;
                cout<<"Please Enter the borrowDate,Follow the fomat YYYY-MM-DD"<<endl;
                cin>>bdate;
                addRecord(BookBorrow(bid,uid,bdate));
            }
            case 2:{
                listRecords();
            }
            case 3:{
                int userID;
                cout << "Enter User ID to view history: ";
                cin >> userID;
                userHistory(userID);
                break;
            }
            case 4:{
                int bookID;
                cout << "Enter Book ID to view history: ";
                cin >> bookID;
                bookHistory(bookID);
                break;
            }
            case 5: {
                return; // 返回主菜单
            }
        }
    }
};