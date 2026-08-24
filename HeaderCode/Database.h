#pragma once
#include <iostream>
#include <string>
#include <mysqlx/xdevapi.h>
#include <memory>
using namespace std;

class Database{
    private:
    string host;
    string user;
    string password;
    string database;
    int port;
    unique_ptr<mysqlx::Session> session;

    public:
    Database();
    ~Database();
    void Connect();
    void Disconnect();

    bool AdminAuth(string& username, string& password);
    void viewAdmin();
    void updateAdmin(int choice, string username, string change);
    void createAdmin(string username, string pw, string adminname);
    void deleteAdmin(string username);
    // void ExecuteQuery(string query);

    double getBeveragePrice(string BeverageName);
    double getSizePrice(string SizeName);
    double getAddOnPrice(string AddOnName);
        
};