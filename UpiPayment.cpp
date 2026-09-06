// SOLID: Open/Closed Principle (OCP) & Liskov Substitution Principle (LSP)
#pragma once
#include "Payment.cpp"
#include <string>
#include <iostream>
using namespace std;

class UpiPayment : public Payment {
private:
    string upiId;

public:
    UpiPayment(string upiId, double amount) : Payment(amount) {
        this->upiId = upiId;
    }

    bool pay(double amount) {
        if (upiId.find('@') == string::npos) {
            cout << "  [UPI] Payment FAILED -- \"" << upiId << "\" is not a valid UPI id" << endl;
            return false;
        }
        cout << "  [UPI] Rs." << amount << " paid successfully" << endl;
        return true;
    }
};