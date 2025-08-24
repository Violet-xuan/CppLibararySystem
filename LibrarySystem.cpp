#include<string.h>
#include<iostream>
#include<chrono>
#include"BookManager.h"
#include"UserManager.h"
#include"RecordManager.h"
#include"BookBorrow.h"
using namespace std;
BookManager bookManager;
UserManager userManager;
RecordManager recordManager;
void welcomePage() {
    cout << "Welcome to the Library Management System!" << endl;
    cout<<"1.Administrator"<<endl;
    cout<<"2.User"<<endl;
    cout << "3.Exit" << endl;
    cout<<"Please select your choice (1-3): "<<endl;
}
void adminPage(){
    cout << "Administrator Mode" << endl;
    cout << "1. Book Management" << endl;
    cout << "2. User Management" << endl;
    cout << "3. Record Management" << endl;
    cout << "4. Return to Main Menu" << endl;
    cout << "Please select an option (1-4): ";
    int adminChoice;
    cin >> adminChoice;
    switch (adminChoice) {
        case 1:
            bookManager.bookManagementPage();
            break;
        case 2:
            userManager.UserManagementPage();
            break;
        case 3:
            recordManager.recordManagementPage();
            break;
        case 4:
            break; // 返回主菜单
        default:
            cout << "Invalid option. Please try again." << endl;
            break;
    }        
}
void userPage(){
    cout << "User Mode" << endl;
    cout << "1. Book Search" << endl;
    cout << "2. Borrow Book" << endl;
    cout << "3. Return Book" << endl;
    cout << "4. View Borrow History" << endl;
    cout << "5. Return to Main Menu" << endl;
    cout << "Please select an option (1-5): ";
    int userChoice;
    cin >> userChoice;
    switch (userChoice) {
        case 1:
            bookManager.bookSearchPage();
            break;
        case 2: {
            int bookID, userID;
            cout << "Enter Book ID to borrow: ";
            cin >> bookID;
            cout << "Enter User ID: ";
            cin >> userID;
            User *targetUser=userManager.findUser(userID);
            Book *targetBook=bookManager.findBook(bookID);
            if(targetBook->getBookStatus()&&targetUser->getBorrowedCount()<10){
                recordManager.addRecord(BookBorrow(bookID, userID));
                targetBook->updateStatus(false);
                targetUser->borrowBook(bookID);
                cout << "Book borrowed successfully!" << endl<<endl;
            }
            else{
                cout<<"Bookborrow Fail,Please check the book's availibility or the User's BorrowedBooks Count"<<endl<<endl;
            }
            break;
        }
        case 3: {
            int bookID, userID;
            cout << "Enter Book ID to return: ";
            cin >> bookID;
            cout << "Enter User ID: ";
            cin >> userID;// 假设有一个方法来处理归还逻辑
            recordManager.returnBook(bookID, userID);
            cout << "Book returned successfully!" << endl;
            break;
        }
        case 4:
            recordManager.listRecords();
            break;
        case 5:
            break; // 返回主菜单
        default:
            cout << "Invalid option. Please try again." << endl;
    }
}
int main(){
    while(1){
        welcomePage();
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: {
                adminPage();
                break;
            }
            case 2: {
                userPage();
                break;
            }
            case 3:{
                cout << "Exiting the system. Goodbye!" << endl;
                return 0;
            }
            default:{
                cout << "Invalid option. Please try again." << endl;
            }
        }
    }
}
