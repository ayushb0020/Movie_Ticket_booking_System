// SOLID: Single Responsibility Principle (SRP
#pragma once

#include <string>
using namespace std;

enum class SeatType { SILVER, GOLD, PLATINUM };


const double SILVER_PRICE   = 150.0;
const double GOLD_PRICE     = 250.0;
const double PLATINUM_PRICE = 400.0;

class Seat {
private:
    string seatNumber;
    SeatType type;

public:
    Seat(string seatNumber, SeatType type) 
    {
        this->seatNumber = seatNumber;
        this->type = type;
    }

    string getSeatNumber() 
    {
         return seatNumber; 
    }
    SeatType getType()     
    { 
        return type; 
    }

    double getPrice() {
        if (type == SeatType::SILVER)  
        {
             return SILVER_PRICE;
        }
        if (type == SeatType::GOLD)
        {
            return GOLD_PRICE;
        }
        return PLATINUM_PRICE;
    }

    string getTypeName() {
        if (type == SeatType::SILVER)   
        {
            return "SILVER";
        }
        if (type == SeatType::GOLD)    
        { 
            return "GOLD";
        }

        return "PLATINUM";
    }
};
