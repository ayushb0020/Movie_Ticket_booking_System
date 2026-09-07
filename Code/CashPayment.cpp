#pragma once
#include "Payment.cpp"
#include <string>
#include <iostream>
using namespace std;

class CashPayment : public Payment {
private:
    double cashGiven;

public:
    CashPayment(double cashGiven, double amount) : Payment(amount) {
        this->cashGiven = cashGiven;
    }

    bool pay(double amount) {
        if (cashGiven < amount) {
            cout << "  [CASH] Payment FAILED -- cash given is less than the amount due" << endl;
            return false;
        }
        cout << "  [CASH] Rs." << amount << " paid successfully" << endl;
        return true;
    }
};