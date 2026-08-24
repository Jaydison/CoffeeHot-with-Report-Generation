#ifndef ADMIN_H
#define ADMIN_H
#include <iostream>
#include <string>
using namespace std;

class Database;

class Admin{
    private:
    string username;
    string password = "root";
    int retry = 0;
    Database& database;

    public:
    explicit Admin(Database& database);
    bool Confirmation();
    bool Login();
    void Logout();
    void Menu();
    void AdminMenu();
};

#endif