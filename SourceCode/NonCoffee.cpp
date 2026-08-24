#include <iostream>
#include <cstdlib>
#include <string>
#include "NonCoffee.h"
using namespace std;

NonCoffee::NonCoffee(){};

void NonCoffee::MenuDisplay(){
    cout << "Welcome to the Coffee Menu!" << endl;
    cout << "1. Hot Chocolate" << endl;
    cout << "2. Matcha Latte" << endl;
    cout << "3. Milk Tea" << endl;
    cout << "4. Vanilla Milk" << endl;
    cout << "5. Back to Main Menu" << endl;
}

string NonCoffee::GetChoice(){
    int choice;
    cout << "Enter your choice: ";
    cin >> choice; 
    cin.clear();
    cin.ignore(1024, '\n');
    system("cls");
    
    if(cin.fail()){
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "Invalid input. Please enter a number." << endl;
        return GetChoice();
    }
    while(choice < 1 || choice > 5){
        cout << "Invalid choice. Please try again." << endl;
        return GetChoice();
    }

    string NonCoffeeNames[] = {"Hot Chocolate", "Matcha Latte", "Milk Tea", "Vanilla Milk"};


    if(choice == 5){
        return "exit";
    }
    return NonCoffeeNames[choice - 1];;
}

