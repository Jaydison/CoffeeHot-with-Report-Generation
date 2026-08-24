#ifndef CUSTOMIZE_H
#define CUSTOMIZE_H
#include <iostream>
#include <string>
using namespace std;

class Customize{
    public:

    struct Coffee{
        string size;
        string sugarLevel;
        string IceLevel;
        string temperature;
        string addOns;
        double price;
    };

    struct NonCoffee{
        string size;
        string sugarLevel;
        string IceLevel;
        string temperature;
        string addOns;
        double price;
    };

    struct Juices{
        string size;
        string sugarLevel;
        string IceLevel;
        double price;
    };

    Customize();
    int CustomizeDrink(Coffee& coffee, string name);
    int CustomizeDrink(NonCoffee& noncoffee, string name);
    int CustomizeDrink(Juices& juices, string name);

};

#endif