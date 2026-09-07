//SOLID: Dependency Inversion Principle (DIP)
#pragma once

#include "Customer.cpp"
#include "Booking.cpp"
#include "PriceCalculator.cpp"
#include "TicketPrinter.cpp"
#include "Payment.cpp"

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class BookingService {
private:
    vector<Booking*> bookings;
    PriceCalculator priceCalculator;
    TicketPrinter ticketPrinter;

public:
    // F4 + F5: validate every seat first; reject the WHOLE booking if any
    // seat is invalid or already booked, with NO state changed (FR4).
    Booking* bookSeats(Show* show, Customer* customer, vector<string> seatNumbers) {
        vector<ShowSeat*> chosen;

        for (int i = 0; i < (int)seatNumbers.size(); i++) {
            ShowSeat* ss = show->findShowSeat(seatNumbers[i]);
            if (ss == nullptr) {
                cout << "  Invalid seat number: " << seatNumbers[i] << endl;
                return nullptr; // edge case 4
            }
            if (!ss->isAvailable()) {
                cout << "  Seat " << seatNumbers[i] << " is already BOOKED. Booking rejected." << endl;
                return nullptr; // edge case 1 -- nothing changes
            }
            chosen.push_back(ss);
        }

        double total = priceCalculator.calculateTotal(chosen);
        Booking* booking = new Booking(show, customer, chosen, total);

        // Only mark seats BOOKED once every seat in the request is known valid.
        for (int i = 0; i < (int)chosen.size(); i++) chosen[i]->book();

        bookings.push_back(booking);
        return booking;
    }

    // F6: a failed payment must NOT confirm the booking, and must release the seats
    bool makePayment(Booking* booking, Payment* payment) {
        bool success = payment->pay(booking->getTotalAmount()); // RUNTIME POLYMORPHISM
        if (success) {
            booking->confirm();
            ticketPrinter.printTicket(booking); // F7
        } else {
            booking->fail();
            cout << "  Booking " << booking->getBookingId() << " NOT confirmed. Seats released." << endl;
        }
        return success;
    }

    // F8: cancel -- only a CONFIRMED booking belonging to this customer can be cancelled
    bool cancelBooking(string bookingId, Customer* customer) {
        Booking* booking = findBooking(bookingId, customer);
        if (booking == nullptr) {
            cout << "  No such booking for this customer." << endl; // edge case 4
            return false;
        }
        if (booking->getStatus() != BookingStatus::CONFIRMED) {
            cout << "  Only a CONFIRMED booking can be cancelled." << endl;
            return false;
        }
        booking->cancelBooking();
        cout << "  Booking " << bookingId << " cancelled. Seats are AVAILABLE again." << endl;
        return true;
    }

    vector<Booking*> getBookingsFor(Customer* customer) {
        vector<Booking*> result;
        for (int i = 0; i < (int)bookings.size(); i++) {
            if (bookings[i]->getCustomer() == customer) result.push_back(bookings[i]);
        }
        return result;
    }

private:
    Booking* findBooking(string bookingId, Customer* customer) {
        for (int i = 0; i < (int)bookings.size(); i++) {
            if (bookings[i]->getBookingId() == bookingId && bookings[i]->getCustomer() == customer) {
                return bookings[i];
            }
        }
        return nullptr;
    }
};

