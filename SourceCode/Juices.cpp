#include <iostream>
#include <cstdlib>
#include <string>
#include "Juices.h"
using namespace std;

Juices::Juices(){};

void Juices::MenuDisplay(){
    cout << "Welcome to the Coffee Menu!" << endl;
    cout << "1. Orange Juice" << endl;
    cout << "2. Apple Juice" << endl;
    cout << "3. Mango Juice" << endl;
    cout << "4. Watermelon Juice" << endl;
    cout << "5. Back to Main Menu" << endl;
}

string Juices::GetChoice(){
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

    string Juices[] = {"Orange Juice", "Apple Juice", "Mango Juice", "Watermelon Juice"};


    if(choice == 5){
        return "exit";
    }
    return Juices[choice - 1];;
}

