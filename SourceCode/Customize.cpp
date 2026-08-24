#include <iostream>
#include <cstdlib>
#include <string>
#include "..\HeaderCode\Customize.h"
using namespace std;

int choice;
char retry;

Customize::Customize(){}

int ChoicePrompt(string Title, string Option1, string Option2, string Option3, string ChoiceName){
    cout << "Choose your " << Title << " for " << ChoiceName << " :" << endl;
    cout << "1: " << Option1 << endl;
    cout << "2: " << Option2 << endl;
    cout << "3: " << Option3 << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.clear();
    cin.ignore(1024, '\n');
    system("cls");

    if(cin.fail()){
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "Invalid input. Please enter a number." << endl;
        return ChoicePrompt(Title, Option1, Option2, Option3, ChoiceName);
    }
    while(choice < 1 || choice > 3){
        cout << "Invalid choice. Please try again." << endl;
        choice = ChoicePrompt(Title, Option1, Option2, Option3, ChoiceName);
    }
    system("cls");
    return choice;
}

int Customize::CustomizeDrink(Customize::Coffee& coffee, string name){
    cout << "Customize your " << name << " here!" << endl;
    int sizeChoice = ChoicePrompt("size", "Small", "Medium", "Large", name);
    int sugarChoice = ChoicePrompt("sugar level", "No sugar", "Less sugar", "Regular sugar", name);
    int tempChoice = ChoicePrompt("temperature", "Hot", "Warm", "Cold", name);
    int iceChoice = 1;
    if(tempChoice == 3){
        iceChoice = ChoicePrompt("ice level", "No ice", "Less ice", "Regular ice", name);
    }
    int addOnsChoice = ChoicePrompt("add-ons", "None", "Whipped Cream", "Caramel Sauce", name);

    string sizes[] = {"Small", "Medium", "Large"};
    string sugarLevels[] = {"No sugar", "Less sugar", "Regular sugar"};
    string iceLevels[] = {"No ice", "Less ice", "Regular ice"};
    string temperatures[] = {"Hot", "Warm", "Cold"};
    string addOnsOptions[] = {"None", "Whipped Cream", "Caramel Sauce"};

    cout << "You have chosen the following options:" << endl;
    cout << "Beverage: " << name << endl; 
    cout << "Size: " << sizes[sizeChoice - 1] << endl;
    cout << "Sugar Level: " << sugarLevels[sugarChoice - 1] << endl;
    cout << "Temperature: " << temperatures[tempChoice - 1] << endl;
    if(iceChoice == 3){
        cout << "Ice Level: " << iceLevels[iceChoice - 1] << endl;
    }
    cout << "Add-ons: " << addOnsOptions[addOnsChoice - 1] << endl;
    cout << "Confirm your order? Y/N" << endl;
    cout << "Enter your choice: ";
    cin >> retry;
    cin.clear();
    cin.ignore(1024, '\n');
    system("cls");

    if(cin.fail() || (retry != 'Y' && retry != 'y' && retry != 'N' && retry != 'n')){
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "Invalid input. Please enter Y or N." << endl;
        CustomizeDrink(coffee, name);
    }
    if(retry == 'Y' || retry == 'y'){
        cout << "Your drink has been customized!" << endl;
        coffee.size = sizes[sizeChoice - 1];
        coffee.sugarLevel = sugarLevels[sugarChoice - 1];
        coffee.IceLevel = iceLevels[iceChoice - 1];
        coffee.temperature = temperatures[tempChoice - 1];
        coffee.addOns = addOnsOptions[addOnsChoice - 1];
        return 0;
    }else{
        return 1;
    }
}

int Customize::CustomizeDrink(Customize::NonCoffee& noncoffee, string name){
    cout << "Customize your " << name << " here!" << endl;
    int sizeChoice = ChoicePrompt("size", "Small", "Medium", "Large", name);
    int sugarChoice = ChoicePrompt("sugar level", "No sugar", "Less sugar", "Regular sugar", name);
    int tempChoice = ChoicePrompt("temperature", "Hot", "Warm", "Cold", name);
    int iceChoice = 1;
    if(tempChoice == 3){
        iceChoice = ChoicePrompt("ice level", "No ice", "Less ice", "Regular ice", name);
    }
    int addOnsChoice = ChoicePrompt("add-ons", "None", "Whipped Cream", "Caramel Sauce", name);

    string sizes[] = {"Small", "Medium", "Large"};
    string sugarLevels[] = {"No sugar", "Less sugar", "Regular sugar"};
    string iceLevels[] = {"No ice", "Less ice", "Regular ice"};
    string temperatures[] = {"Hot", "Warm", "Cold"};
    string addOnsOptions[] = {"None", "Whipped Cream", "Caramel Sauce"};

    cout << "You have chosen the following options:" << endl;
    cout << "Beverage: " << name << endl; 
    cout << "Size: " << sizes[sizeChoice - 1] << endl;
    cout << "Sugar Level: " << sugarLevels[sugarChoice - 1] << endl;
    cout << "Temperature: " << temperatures[tempChoice - 1] << endl;
    if(iceChoice == 3){
        cout << "Ice Level: " << iceLevels[iceChoice - 1] << endl;
    }
    cout << "Add-ons: " << addOnsOptions[addOnsChoice - 1] << endl;
    cout << "Confirm your order? Y/N" << endl;
    cout << "Enter your choice: ";
    cin >> retry;
    cin.clear();
    cin.ignore(1024, '\n');
    system("cls");

    if(cin.fail() || (retry != 'Y' && retry != 'y' && retry != 'N' && retry != 'n')){
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "Invalid input. Please enter Y or N." << endl;
        CustomizeDrink(noncoffee, name);
    }
    if(retry == 'Y' || retry == 'y'){
        cout << "Your drink has been customized!" << endl;
        noncoffee.size = sizes[sizeChoice - 1];
        noncoffee.sugarLevel = sugarLevels[sugarChoice - 1];
        noncoffee.IceLevel = iceLevels[iceChoice - 1];
        noncoffee.temperature = temperatures[tempChoice - 1];
        noncoffee.addOns = addOnsOptions[addOnsChoice - 1];
        return 0;
    }else{
        return 1;
    }
}

int Customize::CustomizeDrink(Customize::Juices& juices, string name){
    cout << "Customize your " << name << " here!" << endl;
    int sizeChoice = ChoicePrompt("size", "Small", "Medium", "Large", name);
    int sugarChoice = ChoicePrompt("sugar level", "No sugar", "Less sugar", "Regular sugar", name);
    int iceChoice = ChoicePrompt("ice level", "No ice", "Less ice", "Regular ice", name);

    string sizes[] = {"Small", "Medium", "Large"};
    string sugarLevels[] = {"No sugar", "Less sugar", "Regular sugar"};
    string iceLevels[] = {"No ice", "Less ice", "Regular ice"};

    cout << "You have chosen the following options:" << endl;
    cout << "Beverage: " << name << endl; 
    cout << "Size: " << sizes[sizeChoice - 1] << endl;
    cout << "Sugar Level: " << sugarLevels[sugarChoice - 1] << endl;
    cout << "Ice Level: " << iceLevels[iceChoice - 1] << endl;
    while (true){
        cout << "Confirm your order? Y/N\n";
        cout << "Enter your choice: ";
        cin >> retry;
        if (retry == 'Y' || retry == 'y') {
            system("cls");
            break;
        }
        if (retry == 'N' || retry == 'n') {
            system("cls");
            return 1;
        }
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "Invalid input. Please enter Y or N.\n";
    }
    cout << "Your drink has been customized!" << endl;
    juices.size = sizes[sizeChoice - 1];
    juices.sugarLevel = sugarLevels[sugarChoice - 1];
    juices.IceLevel = iceLevels[iceChoice - 1];
    return 0;
}