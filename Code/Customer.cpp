#pragma once

#include <string>
using namespace std;

class Customer {
private:
    string name;
    string phone;

public:
    // Overloaded constructors -- COMPILE-TIME POLYMORPHISM
    Customer(string name, string phone) {
        this->name = name;
        this->phone = phone;
    }

   
    Customer() : Customer("Guest", "N/A") {}

    string getName()  { return name; }
    string getPhone() { return phone; }
};
