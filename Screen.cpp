#pragma once
#include "Seat.cpp"
#include <vector>
#include <string>
using namespace std;

class Screen {
private:
    int screenNumber;
    vector<Seat> seats;

public:
    Screen(int screenNumber) 
    {
        this->screenNumber = screenNumber;
    }

    void addSeat(const Seat& seat) 
    {
        seats.push_back(seat);
    }

    int getScreenNumber() 
    { 
        return screenNumber; 
    }

    string getDisplayName() 
    {
        return "Screen-" + to_string(screenNumber);
    }

    vector<Seat>& getSeats() { return seats; }
};
