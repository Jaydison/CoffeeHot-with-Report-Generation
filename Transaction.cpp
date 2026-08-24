#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "../HeaderCode/Transaction.h"
#include "Payment.h"

using namespace std;

Transaction::Transaction(){}

string getTimestamp()
{
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);

    tm localTime;
    localtime_s(&localTime, &currentTime);

    stringstream ss;

    ss << put_time(&localTime, "%Y-%m-%d %H:%M:%S");

    return ss.str();
}

void Transaction::RecordTransaction(string beverage, double total)
{
    string timestamp = getTimestamp();
    cout << "Transaction recorded at " << timestamp << " with a total of $" << fixed << setprecision(2) << total << endl;
}

void Transaction::DisplayTransaction(
    string beverageName, 
    string sizeName, 
    string sugarName, 
    string tempName, 
    string iceName, 
    string addName){
    cout << endl;
    cout << "You have purchased the following: " << endl;
    cout << fixed << setprecision(2);
    cout << "\n";
    cout << "===================================================\n";
    cout << "| No. | Description                    | Price    |\n";
    cout << "===================================================\n";
    cout << "| " << left << setw(4) << "1."
        << "| " << setw(31) << ("Beverage: " + beverageName)
        << "| " << right << setw(8) << Payment::beveragePrice << " |\n";
    cout << "| " << left << setw(4) << "2."
        << "| " << setw(31) << ("Size: " + sizeName)
        << "| " << right << setw(8) << Payment::sizePrice << " |\n";
    cout << "| " << left << setw(4) << "3."
        << "| " << setw(31) << ("Sugar Level: " + sugarName)
        << "| " << right << setw(8) << 0.00 << " |\n";
    cout << "| " << left << setw(4) << "4."
        << "| " << setw(31) << ("Temperature: " + tempName)
        << "| " << right << setw(8) << 0.00 << " |\n";
    int number = 5;
    if (tempName == "Cold") {
        cout << "| " << left << setw(4) << "5."
            << "| " << setw(31) << ("Ice: " + iceName)
            << "| " << right << setw(8) << 0.00 << " |\n";

        number = 6;
    }
    cout << "| " << left << setw(4) << (to_string(number) + ".")
        << "| " << setw(31) << ("Add-on: " + addName)
        << "| " << right << setw(8) << Payment::addOnPrice << " |\n";
    cout << "===================================================\n";
    cout << "| " << left << setw(37) << "TOTAL"
        << "| " << right << setw(8) << Payment::total << " |\n";
    cout << "===================================================\n";
}