// SOLID: Single Responsibility Principle (SRP
#pragma once
#include "ShowSeat.cpp"
#include "Booking.cpp"

#include <iostream>
#include <vector>
using namespace std;

class TicketPrinter {
public:
    void printTicket(Booking* booking) {
        Show* show = booking->getShow();
        vector<ShowSeat*>& seats = booking->getSeats();

        cout << "  ================ TICKET ================" << endl;
        cout << "   Booking ID : " << booking->getBookingId() << endl;
        cout << "   Movie      : " << show->getMovie()->getTitle() << endl;
        cout << "   Screen     : " << show->getScreen()->getDisplayName()
             << "  " << show->getStartTime() << endl;
        cout << "   Seats      : ";
        for (int i = 0; i < (int)seats.size(); i++) {
            cout << seats[i]->getSeat()->getSeatNumber();
            if (i != (int)seats.size() - 1) cout << ", ";
        }
        cout << endl;
        cout << "   Amount     : Rs." << booking->getTotalAmount()
             << "        Status: " << booking->getStatusName() << endl;
        cout << "  ========================================" << endl;
    }
};
