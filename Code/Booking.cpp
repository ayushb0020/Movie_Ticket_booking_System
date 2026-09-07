#pragma once
#include "Show.cpp"
#include "Customer.cpp"

#include <vector>
#include <string>
using namespace std;

enum class BookingStatus { PENDING, CONFIRMED, CANCELLED, FAILED };

class Booking {
private:
    string bookingId;
    Show* show;
    Customer* customer;
    vector<ShowSeat*> seats;
    double totalAmount;
    BookingStatus status;

    static int nextBookingNumber;

public:
    Booking(Show* show, Customer* customer, vector<ShowSeat*> seats, double totalAmount) {
        nextBookingNumber++;
        this->bookingId = "BK" + to_string(nextBookingNumber);
        this->show = show;
        this->customer = customer;
        this->seats = seats;
        this->totalAmount = totalAmount;
        this->status = BookingStatus::PENDING;
    }

    void confirm() { status = BookingStatus::CONFIRMED; }

    // F6: a failed payment releases the seats and never confirms the booking
    void fail() {
        for (int i = 0; i < (int)seats.size(); i++) seats[i]->cancel();
        status = BookingStatus::FAILED;
    }

    // F8: cancelling a CONFIRMED booking releases its seats
    void cancelBooking() {
        for (int i = 0; i < (int)seats.size(); i++) seats[i]->cancel();
        status = BookingStatus::CANCELLED;
    }

    string getBookingId()          { return bookingId; }
    Show* getShow()                { return show; }
    Customer* getCustomer()        { return customer; }
    vector<ShowSeat*>& getSeats()  { return seats; }
    double getTotalAmount()        { return totalAmount; }
    BookingStatus getStatus()      { return status; }

    string getStatusName() {
        if (status == BookingStatus::CONFIRMED) return "CONFIRMED";
        if (status == BookingStatus::CANCELLED) return "CANCELLED";
        if (status == BookingStatus::FAILED)    return "FAILED";
        return "PENDING";
    }
};

int Booking::nextBookingNumber = 1000; // first booking created will be BK1001

