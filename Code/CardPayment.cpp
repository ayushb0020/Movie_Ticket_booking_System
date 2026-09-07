// SOLID: Open/Closed Principle (OCP) & Liskov Substitution Principle (LSP)
#pragma once
#include "Payment.cpp"
#include <string>
#include <iostream>
using namespace std;

class CardPayment : public Payment 
{
private:
    string cardNumber;

public:
    CardPayment(string cardNumber, double amount) : Payment(amount) {
        this->cardNumber = cardNumber;
    }

    bool pay(double amount) {
        if (cardNumber.size() != 16) {
            cout << "  [CARD] Payment FAILED -- card number must be 16 digits" << endl;
            return false;
        }
        cout << "  [CARD] Rs." << amount << " paid successfully" << endl;
        return true;
    }
};