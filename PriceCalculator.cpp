// SOLID: Single Responsibility Principle (SRP
#pragma once
#include"ShowSeat.cpp"
#include <vector>
using namespace std;

class PriceCalculator {
public:
    double calculateTotal(vector<ShowSeat*> seats) {
        double total = 0;
        for (int i = 0; i < (int)seats.size(); i++) {
            total += seats[i]->getSeat()->getPrice();
        }
        return total;
    }

    // Overloaded for a single seat -- COMPILE-TIME POLYMORPHISM
    double calculateTotal(ShowSeat* seat) {
        return seat->getSeat()->getPrice();
    }
};
