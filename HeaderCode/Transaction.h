#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <iostream>
#include <string>

using namespace std;

class Transaction{
    public:
    Transaction();
    void RecordTransaction(string beverage, double total);
    void DisplayTransaction(string beverageName, string sizeName, string sugarName, string iceName, string tempName, string addName);
};

#endif