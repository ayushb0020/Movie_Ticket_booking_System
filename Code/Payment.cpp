// SOLID: Open/Closed Principle (OCP) & Liskov Substitution Principle (LSP)
#pragma once


class Payment {
protected:
    double amount;

public:
    Payment(double amount) {
        this->amount = amount;
    }

    // Pure virtual -- every child MUST implement pay() and none of them
    // need any extra setup call to work through a Payment* (Liskov Substitution Principle).
    // Substitution Principle).
    virtual bool pay(double amount) = 0;

    virtual ~Payment() {}
};
