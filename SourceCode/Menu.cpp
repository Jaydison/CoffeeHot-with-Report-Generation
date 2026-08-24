#include <iostream>
#include "..\HeaderCode\Menu.h"
using namespace std;

Menu::Menu(){};

void Menu::Display(){
    cout << "Welcome to the Menu!" << endl;
    cout << "1. Coffee" << endl;
    cout << "2. Non Coffee" << endl;
    cout << "3. Juices" << endl;
    cout << "4. Exit" << endl;
    cout << "5. Admin" << endl;
}

int Menu::GetChoice(){
    int choice;
    cout << "Enter your choice (1-5): ";
    cin >> choice;
    system("cls");
    
    if(cin.fail()){
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "Invalid input. Please enter a number." << endl;
        Display();
        return GetChoice();
    }
    while((choice < 1 || choice > 5)){
        cout << "Invalid choice. Please try again." << endl;
        Display();
        return GetChoice();
    }
    return choice;
}