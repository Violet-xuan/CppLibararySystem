#include <vector>
#include <algorithm>
#include"User.h"
#include<fstream>
#include "FileHandle.h"
#pragma once
fstream UserFile("UserData.txt",ios::app);
class UserManager {
private:
    vector<User> users;
public:
    UserManager(){
        ifstream InUserFile("UserData.txt");
        if(!InUserFile){
            cerr<<"Cannot open UserDataFile"<<endl;
            return ;
        }
        int uid;
        string tmpName,tmpEmail;
        while(InUserFile>>uid>>tmpName>>tmpEmail){
            users.push_back(User(uid,tmpName,tmpEmail));
        }
        InUserFile.close();
        cout<<"UserManager Initialization Success!"<<endl;
    }
    void addUser(const User& user) {
        users.push_back(user);
        UserFile<<user.getUserID()<<endl;
    }
    bool deleteUser(const int& userID) {
        auto it = remove_if(users.begin(), users.end(), [&](const User& u){ return u.getUserID() == userID; });
        if (it != users.end()) {
            users.erase(it, users.end());
            removeIdFromFile("UserData.txt",userID);
            return true;
        }
        return false;
    }
    User* findUser(const int& userID) {
        for (auto& user : users) {
            if (user.getUserID() == userID) return &user;
        }
        return nullptr;
    }
    void modifyUser(const int& userID, const string& name, const string& email) {
        User* user = findUser(userID);
        if (user) {
            user->setInfo(name, email);
            cout<<"User Modified Successfully"<<endl;
        }    
    }
    void listUsers() {
        for (const auto& user : users) user.displayUserInfo();
    }
    void UserManagementPage() {
        cout << "User Management Page" << endl;
        cout << "1. Add User" << endl;
        cout << "2. Delete User" << endl;
        cout << "3. Modify User" << endl;
        cout << "4. List Users" << endl;
        cout << "5. Return to Main Menu" << endl;
        cout << "Please select an option (1-5): ";
        if (!UserFile.is_open()) { // 检查是否打开成功
            std::cerr << "Error opening UserFile!" << std::endl;
            return ;
        }
        int UserOption;
        cin>>UserOption;
        switch(UserOption){
            case 1:{
                int id;
                string name, email;
                cout << "Enter User ID: ";
                cin >> id;
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Email: ";
                getline(cin, email);
                addUser(User(id, name, email));
                break;
            } 
            case 2: {
                int id;
                cout << "Enter User ID to delete: ";
                cin >> id;
                if (deleteUser(id)) {
                    cout << "User deleted successfully." << endl;
                } else {
                    cout << "User not found." << endl;
                }
                break;
            }
            case 3:{
                int id;
                cout<<"Please Enter the ID of the User you want to modify:"<<endl;
                cin>>id;
                cout<<"Please Enter the User's New Name"<<endl;
                string name,email;
                cin>>name;
                cout<<"Please Enter the User's new email"<<endl;
                cin>>email;
                modifyUser(id,name,email);
                break;
            }
            case 4:{
                listUsers();
                break;
            }
            case 5:{
                break;
            }
        }
    }
};