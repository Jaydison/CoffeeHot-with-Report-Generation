#ifndef PAYMENT_H
#define PAYMENT_H
#include <iostream>
#include <string>
using namespace std;

class Database;

class Payment{
    private:
    Database& database;

    public:
    static double total;
    static double beveragePrice, sizePrice, addOnPrice;
    explicit Payment(Database& database);
    double CalculateTotal(string beverage, string size, string addOns);
    void DisplayTotal();
    void DisplayPaymentOptions();
    void ProcessPayment();
    
};

#endif