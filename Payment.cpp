#include <iostream>
#include <iomanip>
#include "../HeaderCode/Payment.h"
#include "Database.h"
using namespace std;

double Payment::total = 0;
double Payment::beveragePrice = 0;
double Payment::sizePrice = 0;
double Payment::addOnPrice = 0;

Payment::Payment(Database& database)
    : database(database){
}

double Payment::CalculateTotal(string beverage, string size, string addOns){
    beveragePrice = database.getBeveragePrice(beverage);
    sizePrice = database.getSizePrice(size);
    if(addOns != "None"){
        addOnPrice = database.getAddOnPrice(addOns); 
    }
    Payment::total += beveragePrice;
    Payment::total += sizePrice;
    Payment::total += addOnPrice;

    // struct Option{
    //     string name;
    //     double price;
    // };
    //
    // Option coffeeNames[]{
    //     {"Espresso", 2.50},
    //     {"Latte", 3.00 },
    //     {"Cappuccino", 3.50}
    // };
    //
    // Option coffeeSizes[]{
    //     {"Small", 0.00},
    //     {"Medium", 0.50},
    //     {"Large", 1.00}
    // };
    //
    // Option addOn[]{
    //     {"None", 0.00},
    //     {"Whipped Cream", 0.50},
    //     {"Caramel Sauce", 0.75}
    // };
    //
    // for(auto nameOption : coffeeNames){
    //     if(beverage == nameOption.name){
    //         Payment::total += nameOption.price;
    //     }
    // }
    //
    // for(auto sizeOption : coffeeSizes){
    //     if(size == sizeOption.name){
    //         Payment::total += sizeOption.price;
    //     }
    // }
    //
    // for(auto addOnOption : addOn){
    //     if(addOns == addOnOption.name){
    //         Payment::total += addOnOption.price;
    //     }
    // }
    return Payment::total;
}

void Payment::DisplayTotal(){
    cout << "Your total is: $" << fixed << setprecision(2) << Payment::total << endl;
    cout << endl;
}

void Payment::DisplayPaymentOptions(){
    cout << "Available payment options:" << endl;
    cout << "1. Credit Card" << endl;
    cout << "2. Debit Card" << endl;
    cout << "3. Cash" << endl;
}

void Payment::ProcessPayment(){
    int paymentChoice;
    char choice;
    cout << "Please select a payment option (1-3): ";
    cin >> paymentChoice;
    cout << endl;

    switch(paymentChoice){
        case 1:
            cout << "Processing credit card payment of $" << Payment::total << "..." << endl;
            break;
        case 2:
            cout << "Processing debit card payment of $" << Payment::total << "..." << endl;
            break;
        case 3:
            cout << "Processing cash payment of $" << Payment::total << "..." << endl;
            break;
        default:
            cout << "Invalid payment option. Please try again." << endl;
            ProcessPayment();
            break;
    }

    cout << "Would you like a receipt?" << endl;
    cout << "Your option (Y/N): ";
    cin >> choice;
    if(cin.fail() || (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')){
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "Invalid input. Please enter Y or N." << endl;
    }
    if(choice == 'Y' || choice == 'y'){
        //print receipt
    }
    system("cls");
}