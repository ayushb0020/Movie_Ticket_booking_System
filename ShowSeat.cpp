#pragma once
#include "Seat.cpp"

enum class SeatStatus { AVAILABLE, BOOKED };

class ShowSeat {
private:
    Seat* seat;
    SeatStatus status; // ENCAPSULATION: private, only changed via book()/cancel()

public:
    ShowSeat(Seat* seat) {
        this->seat = seat;
        this->status = SeatStatus::AVAILABLE;
    }

    Seat* getSeat()        { return seat; }
    SeatStatus getStatus() { return status; }
    bool isAvailable()     { return status == SeatStatus::AVAILABLE; }

    bool book() {
        if (!isAvailable()) return false; // validation -- can't double-book
        status = SeatStatus::BOOKED;
        return true;
    }

    void cancel() {
        status = SeatStatus::AVAILABLE;
    }
};

