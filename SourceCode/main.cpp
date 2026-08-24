#include <iostream>
#include "Menu.h"
#include "Coffee.h"
#include "NonCoffee.h"
#include "Juices.h"
#include "Customize.h"
#include "Payment.h"
#include "Transaction.h"
#include "Database.h"
#include "Admin.h"
using namespace std;

int main(){
    string Drink;
    char repurchase;

    Database database;
    Menu menu;
    Coffee coffee;
    NonCoffee noncoffee;
    Juices juices;
    Customize customize;
    Customize::Coffee coffeeCustomize;
    Customize::NonCoffee noncoffeeCustomize;
    Customize::Juices juicesCustomize;
    Payment payment(database);
    Transaction transaction;
    Admin admin(database);

    while(true){
        menu.Display();
        int MenuChoice = menu.GetChoice();

        switch(MenuChoice){
        case 1:
        //This is coffee
        coffee.MenuDisplay();
        Drink = coffee.GetChoice();
        if(Drink != "exit"){
            int customised = customize.CustomizeDrink(coffeeCustomize, Drink);
            if(customised != 1){
                payment.CalculateTotal(Drink, coffeeCustomize.size, coffeeCustomize.addOns);
                payment.DisplayTotal();
                payment.DisplayPaymentOptions();
                payment.ProcessPayment();
                transaction.RecordTransaction(Drink, Payment::total);
                transaction.DisplayTransaction(Drink, coffeeCustomize.size, coffeeCustomize.sugarLevel, coffeeCustomize.IceLevel, coffeeCustomize.temperature, coffeeCustomize.addOns);
                cout << "\nWould you like to make another purchase? (Y/N): " << endl;
                cin >> repurchase;
                if(cin.fail() || (repurchase != 'Y' && repurchase != 'y' && repurchase != 'N' && repurchase != 'n')){
                    cin.clear();
                    cin.ignore(1024, '\n');
                    cout << "Invalid input. Please enter Y or N." << endl;
                }
                if(repurchase == 'N' || repurchase == 'n'){
                    system("cls");
                    return 0;
                }
            }
        }
        system("cls");
        break;

        case 2:
        //This is non-coffee
        noncoffee.MenuDisplay();
        Drink = noncoffee.GetChoice();
        if(Drink != "exit"){
            int customised = customize.CustomizeDrink(noncoffeeCustomize, Drink);
            if(customised != 1){
                payment.CalculateTotal(Drink, noncoffeeCustomize.size, noncoffeeCustomize.addOns);
                payment.DisplayTotal();
                payment.DisplayPaymentOptions();
                payment.ProcessPayment();
                transaction.RecordTransaction(Drink, Payment::total);
                transaction.DisplayTransaction(Drink, noncoffeeCustomize.size, noncoffeeCustomize.sugarLevel, noncoffeeCustomize.IceLevel, noncoffeeCustomize.temperature, noncoffeeCustomize.addOns);
                cout << "\nWould you like to make another purchase? (Y/N): " << endl;
                cin >> repurchase;
                if(cin.fail() || (repurchase != 'Y' && repurchase != 'y' && repurchase != 'N' && repurchase != 'n')){
                    cin.clear();
                    cin.ignore(1024, '\n');
                    cout << "Invalid input. Please enter Y or N." << endl;
                }
                if(repurchase == 'N' || repurchase == 'n'){
                    system("cls");
                    return 0;
                }
            }
        }
        system("cls");
        break;

        case 3:
        //This is juice
        juices.MenuDisplay();
        Drink = juices.GetChoice();
        if(Drink != "exit"){
            int customised = customize.CustomizeDrink(juicesCustomize, Drink);
            if(customised != 1){
                payment.CalculateTotal(Drink, juicesCustomize.size, "None");
                payment.DisplayTotal();
                payment.DisplayPaymentOptions();
                payment.ProcessPayment();
                transaction.RecordTransaction(Drink, Payment::total);
                transaction.DisplayTransaction(Drink, juicesCustomize.size, juicesCustomize.sugarLevel, "Cold", juicesCustomize.IceLevel, "None");
                cout << "\nWould you like to make another purchase? (Y/N): ";
                cin >> repurchase;
                if(cin.fail() || (repurchase != 'Y' && repurchase != 'y' && repurchase != 'N' && repurchase != 'n')){
                    cin.clear();
                    cin.ignore(1024, '\n');
                    cout << "Invalid input. Please enter Y or N." << endl;
                }
                if(repurchase == 'N' || repurchase == 'n'){
                    system("cls");
                    return 0;
                }
            }
        }
        system("cls");
        break;

        case 4:
        cout << "This is exit" << endl;
        cin.get();
        return 0;

        case 5:
        if(admin.Confirmation()){
            if(admin.Login()){
                admin.Menu();
            }
        }
        break;

        default:
        cout << "Invalid input" << endl;
        }

        // if(MenuChoice != 5){
        //     payment.CalculateTotal(Drink, coffeeCustomize.size, coffeeCustomize.addOns);
        //     payment.DisplayTotal();
        //     payment.DisplayPaymentOptions();
        //     payment.ProcessPayment();
        //     transaction.RecordTransaction(Drink, coffeeCustomize.size, coffeeCustomize.addOns, Payment::total);
        //     transaction.DisplayTransaction(Drink, coffeeCustomize.size, coffeeCustomize.sugarLevel, coffeeCustomize.IceLevel, coffeeCustomize.temperature, coffeeCustomize.addOns);
        //     return main();
        // }
    }

    return 0;
}