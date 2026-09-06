# Movie Ticket Booking System

A menu-driven C++ console application for booking movie tickets at a single
cinema — built for **TCS-504 (System Design), Assignment 1**.

## Features

| # | Feature |
|---|---------|
| F1 | List all movies currently playing |
| F2 | List a chosen movie's shows (screen + start time) |
| F3 | Display a show's seat layout (AVAILABLE / BOOKED) |
| F4 | Book one or more seats (rejects the whole booking if any seat is already booked) |
| F5 | Price the booking by seat type — SILVER ₹150, GOLD ₹250, PLATINUM ₹400 |
| F6 | Pay by UPI, Card, or Cash — a failed payment does **not** confirm the booking |
| F7 | Print a ticket (booking id, movie, screen, time, seats, amount) |
| F8 | Cancel a booking — its seats become AVAILABLE again |

## Build & run

No header files are used (one class per `.cpp` file, per course rules), so
every class file is pulled into a single translation unit through
`main.cpp`. **Compile only `main.cpp`:**

```bash
g++ -std=c++11 main.cpp -o booking_app
./booking_app
```

Do not compile the other `.cpp` files separately — they are not standalone
translation units.

## Project structure

One class per file:

```
Movie.cpp          Seat.cpp           Screen.cpp
Cinema.cpp         Show.cpp           ShowSeat.cpp
Customer.cpp       Booking.cpp        Payment.cpp
UpiPayment.cpp      CardPayment.cpp    CashPayment.cpp
PriceCalculator.cpp TicketPrinter.cpp  BookingService.cpp
main.cpp
```

## Design notes

- **Composition**: `Cinema` → `Screen`, `Screen` → `Seat`, `Show` → `ShowSeat`
  (the owner creates and destroys these; lifetime is tied together).
- **Aggregation**: `Show` → `Movie`, `Booking` → `ShowSeat` (borrowed
  references; the part outlives the whole).
- **Association**: `Customer` ↔ `BookingService` (neither owns the other).
- **Inheritance / Abstraction**: `Payment` is an abstract base with a pure
  virtual `pay()`; `UpiPayment`, `CardPayment`, `CashPayment` implement it.
- **Polymorphism**: `BookingService::makePayment` calls `payment->pay(...)`
  through a `Payment*`, dispatching to the correct override at runtime.

## Edge cases handled

1. Booking a seat that's already `BOOKED` → rejected, nothing changes.
2. A failed payment → booking not confirmed, seats released back to available.
3. Cancelling a booking → its seats become `AVAILABLE` again.
4. Invalid seat number or menu choice → a clear message, no crash.

## Author

Submitted for TCS-504, B.Tech CSE Semester 5.
