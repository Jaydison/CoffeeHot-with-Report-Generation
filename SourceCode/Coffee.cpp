#include <iostream>
#include <cstdlib>
#include <string>
#include "..\HeaderCode\Coffee.h"
using namespace std;

Coffee::Coffee(){};

void Coffee::MenuDisplay(){
    cout << "Welcome to the Coffee Menu!" << endl;
    cout << "1. Espresso" << endl;
    cout << "2. Americano" << endl;
    cout << "3. Cappucino" << endl;
    cout << "4. Cafe Latte" << endl;
    cout << "5. Caramel Macchiato" << endl;
    cout << "6. Cafe Mocha" << endl;
    cout << "7. Back to Main Menu" << endl;
}

string Coffee::GetChoice(){
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
    while(choice < 1 || choice > 7){
        cout << "Invalid choice. Please try again." << endl;
        return GetChoice();
    }

    string CoffeeNames[] = {"Espresso", "Americano", "Cappuccino", "Cafe Latte", "Caramel Macchiato", "Cafe Mocha"};

    if(choice == 7){
        return "exit";
    }
    return CoffeeNames[choice - 1];;
}

