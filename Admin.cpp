#include <iostream>
#include <string>
#include <conio.h>
#include "Admin.h"
#include "Database.h"
using namespace std;

int UpdateAdminMenu();
int MenuChoice();

Admin::Admin(Database& database)
    : database(database){
}

bool Admin::Confirmation(){
    char choice;
    cout << "This is admin mode. Would you like to continue?" << endl;
    cout << "Enter your choice (Y/N): ";
    cin >> choice;
    system("cls");

    if(cin.fail() || (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')){
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "Invalid input. Please enter Y or N." << endl;
        return Confirmation();
    }
    if(choice == 'Y' || choice == 'y'){
        return 1;
    }else{
        return 0;
    }
}

bool Admin::Login(){
    if (Admin::retry >= 3)
    {
        cout << "Max attempts reached" << endl;
        cout << "Require super admin to reset" << endl;
        return false;
    }

    cout << "Admin login" << endl;
    cout << "Enter username: ";
    cin >> Admin::username;
    cout << "Enter password: ";
    Admin::password.clear();

    while (true)
    {
        char key = static_cast<char>(_getch());
        // Enter key
        if (key == '\r')
        {
            cout << endl;
            break;
        }
        // Backspace key
        if (key == '\b')
        {
            if (!Admin::password.empty())
            {
                Admin::password.pop_back();

                // Remove the last asterisk from the console
                cout << "\b \b";
            }
        }
        // Special keys, such as arrow keys
        else if (key == 0 || key == static_cast<char>(224))
        {
            // Consume the second special-key code
            _getch();
        }
        // Store and mask normal characters
        else
        {
            Admin::password.push_back(key);
            cout << '*';
        }
    }

    if (database.AdminAuth(Admin::username, Admin::password))
    {
        system("cls");
        cout << "Successfully logged in" << endl;
        Admin::retry = 0;
        return true;
    }
    Admin::retry++;
    if (Admin::retry >= 3)
    {
        cout << "Max attempts reached" << endl;
        cout << "Require super admin to reset" << endl;
        cout << endl;
        return false;
    }
    cout << "Incorrect username or password." << endl;
    cout << "Attempts remaining: " << 3 - Admin::retry << endl;
    cout << "Press any key to try again..." << endl;
    _getch();
    system("cls");
    return Login();
}

void Admin::Logout(){
    cout << "log out :)";
}

void Admin::Menu(){
    int choices = MenuChoice();

    switch(choices){
        case 1:
        cout << "Manage Admins" << endl;
        AdminMenu();
        break;

        case 2:
        cout << "Manage Beverages";
        break;

        case 3:
        cout << "Manage Categories";
        break;

        case 4:
        cout << "Manage Payment";
        break;

        case 5:
        cout << "View Transaction";
        break;

        case 6:
        cout << "View/Add Stock";
        break;

        case 7:
        cout << "Generate Report";
        break;

        case 8:
        Logout();
        break;

        default:
        cout << "Invalid input" << endl;
        break;
    }
}

int MenuChoice(){
    int choices;
    cout << endl;
    cout << "This is Admin Menu" << endl;
    cout << "1. Manage Admins" << endl;
    cout << "2. Manage Beverages" << endl;  
    cout << "3. Manage Categories" << endl;
    cout << "4. Manage Payments" << endl;
    cout << "5. View Transactions" << endl;
    cout << "6. View/Add Stock" << endl;
    cout << "7. Generate Reports" << endl;
    cout << "8. Logout" << endl;
    cout << "Your options: ";
    cin >> choices;
    if(cin.fail()){
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "Invalid input. Please enter a number." << endl;
        return MenuChoice();
    }
    while(choices < 1 || choices > 8){
        cout << "Invalid choice. Please try again." << endl;
        return MenuChoice();
    }
    return choices;
}

void Admin::AdminMenu(){
    string change;
    char letterChoice;
    int choice, UpdateChoice;
    string username, pw, adminname;
    system("cls");
    cout << "Admin Management Menu" << endl;
    cout << "1. Create Admins" << endl;
    cout << "2. View Admins" << endl;
    cout << "3. Update Admins" << endl;
    cout << "4. Remove Admins" << endl;
    cout << "5. Exit" << endl;
    cout << "Your Options: ";
    cin >> choice;
    if(cin.fail()){
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "Invalid input. Please enter a number." << endl;
        return Admin::AdminMenu();
    }
    while(choice < 1 || choice > 5){
        cout << "Invalid choice. Please try again." << endl;
        return Admin::AdminMenu();
    }

    switch(choice){
        case 1:
        cout << "Create Admins" << endl;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> pw;
        cout << "Enter admin name: ";
        cin >> adminname;
        database.createAdmin(username, pw, adminname);
        cout << "Press any key to continue..." << endl;
        cin.clear();
        cin.ignore(1024, '\n');
        if(cin.get()){
            AdminMenu();
        }
        break;

        case 2:
        cout << "View admin" << endl;
        cout << endl;
        system("cls");
        database.viewAdmin();
        cout << "Press any key to continue..." << endl;
        cin.clear();
        cin.ignore(1024, '\n');
        if(cin.get()){
            AdminMenu();
        }
        break;

        case 3:
        UpdateChoice = UpdateAdminMenu();
        // cout << "1. Username" << endl;
        // cout << "2. Password" << endl;
        // cout << "3. Admin Role" << endl;
        // cout << "4. Status" << endl;
        switch(UpdateChoice){
            case 1:
            cout << "Username you want to change: ";
            cin >> username;
            cout << "New username: ";
            cin >> change;
            database.updateAdmin(UpdateChoice, username, change);
            break;

            case 2:
            cout << "Username password you want to change: ";
            cin >> username;
            cout << "New password: ";
            cin >> change;
            database.updateAdmin(UpdateChoice, username, change);
            break;
            
            case 3: 
            cout << "Username role you want to change: ";
            cin >> username;
            cout << "New role: ";
            cin >> change;
            database.updateAdmin(UpdateChoice, username, change);
            break;

            case 4: 
            cout << "Username status you want to change: ";
            cin >> username;
            cout << "New status: ";
            cin >> change;
            database.updateAdmin(UpdateChoice, username, change);
            break;

            case 5:
            break;
        }
        cout << "Press any key to continue..." << endl;
        cin.clear();
        cin.ignore(1024, '\n');
        if(cin.get()){
            AdminMenu();
        }
        break;

        case 4:
        cout << "Delete admin" << endl;
        cout << "Enter the username you want to remove" << endl;
        cout << "Username: ";
        cin >> username;
        cout << "Are you sure you want to remove " << username << "?" << endl;
        cout << "Enter your choice (Y/N): ";
        cin >> letterChoice;
        if(cin.fail() || (letterChoice != 'Y' && letterChoice != 'y' && letterChoice != 'N' && letterChoice != 'n')){
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "Invalid input. Please enter Y or N." << endl;
        }
        if(letterChoice == 'Y' || letterChoice == 'y'){
            database.deleteAdmin(username);
        }else{
            AdminMenu();
        }
        cout << "Press any key to continue..." << endl;
        cin.clear();
        cin.ignore(1024, '\n');
        if(cin.get()){
            AdminMenu();
        }
        break;

        case 5:
        Logout();
    }
}

int UpdateAdminMenu(){
    int choice;
    cout << "Update admin" << endl;
    cout << "What would you like to update?" << endl;
    cout << "1. Username" << endl;
    cout << "2. Password" << endl;
    cout << "3. Admin Role" << endl;
    cout << "4. Status" << endl;
    cout << "5. Exit" << endl;
    cout << "Your choice: ";
    cin >> choice;
    if(cin.fail()){
    cin.clear();
    cin.ignore(1024, '\n');
    cout << "Invalid input. Please enter a number." << endl;
    return UpdateAdminMenu();
    }
    while(choice < 1 || choice > 5){
        cout << "Invalid choice. Please try again." << endl;
        return UpdateAdminMenu();
    }
    cout << endl;
    system("cls");
    return choice;
}