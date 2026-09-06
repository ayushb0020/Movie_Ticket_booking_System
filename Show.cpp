#pragma once
#include "Movie.cpp"
#include "Screen.cpp"
#include "ShowSeat.cpp"

#include <vector>
#include <string>
#include <iostream>
#include <cctype>
using namespace std;

class Show {
private:
    Movie* movie;
    Screen* screen;
    string startTime;
    vector<ShowSeat> showSeats;

    string toUpperCopy(string s) {
        for (int i = 0; i < (int)s.size(); i++) s[i] = toupper(s[i]);
        return s;
    }

    // Printing only -- must not change any state (Clean Code: no side effects)
    void printRow(SeatType type, string label) {
        cout << "  " << label << " ";
        for (int i = 0; i < (int)showSeats.size(); i++) {
            Seat* s = showSeats[i].getSeat();
            if (s->getType() == type) {
                cout << s->getSeatNumber() << (showSeats[i].isAvailable() ? "[ ] " : "[X] ");
            }
        }
        cout << endl;
    }

public:
    Show(Movie* movie, Screen* screen, string startTime) {
        this->movie = movie;
        this->screen = screen;
        this->startTime = startTime;

        vector<Seat>& physicalSeats = screen->getSeats();
        for (int i = 0; i < (int)physicalSeats.size(); i++) {
            showSeats.push_back(ShowSeat(&physicalSeats[i]));
        }
    }

    Movie* getMovie()      { return movie; }
    Screen* getScreen()    { return screen; }
    string getStartTime()  { return startTime; }
    vector<ShowSeat>& getShowSeats() { return showSeats; }

    // F3: display the seat layout with AVAILABLE / BOOKED status
    void displaySeats() {
        cout << "  " << toUpperCopy(screen->getDisplayName()) << "  " << startTime
             << "  |  " << movie->getTitle() << endl;
        printRow(SeatType::SILVER,   "SILVER  ");
        printRow(SeatType::GOLD,     "GOLD    ");
        printRow(SeatType::PLATINUM, "PLATINUM");
        cout << "  ( [ ] = available   [X] = booked )" << endl;
    }

    // Returns nullptr for an unknown seat number -- caller handles the edge case
    ShowSeat* findShowSeat(string seatNumber) {
        for (int i = 0; i < (int)showSeats.size(); i++) {
            if (showSeats[i].getSeat()->getSeatNumber() == seatNumber) {
                return &showSeats[i];
            }
        }
        return nullptr;
    }
};
