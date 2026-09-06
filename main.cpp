
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

#include "Movie.cpp"
#include "Seat.cpp"
#include "Screen.cpp"
#include "Cinema.cpp"
#include "ShowSeat.cpp"  
#include "Show.cpp"
#include "Customer.cpp"
#include "Payment.cpp"
#include "UpiPayment.cpp"
#include "CardPayment.cpp"
#include "CashPayment.cpp"
#include "Booking.cpp"
#include "PriceCalculator.cpp"
#include "TicketPrinter.cpp"
#include "BookingService.cpp"

// ---------------- small input helpers (edge case 4: no crash on bad input) ----------------

int readMenuChoice() {
    string line;
    getline(cin, line);
    stringstream ss(line);
    int choice = -1;
    if (!(ss >> choice)) return -1; // non-numeric input -> caller treats as invalid
    return choice;
}

vector<string> splitSeats(string line) {
    vector<string> result;
    stringstream ss(line);
    string token;
    while (getline(ss, token, ',')) {
        while (!token.empty() && token.front() == ' ') token.erase(token.begin());
        while (!token.empty() && token.back() == ' ') token.pop_back();
        if (!token.empty()) result.push_back(token);
    }
    return result;
}

// ---------------- F1: list all movies currently playing ----------------

void listMovies(vector<Movie>& movies) {
    cout << endl;
    for (int i = 0; i < (int)movies.size(); i++) {
        cout << "  [" << (i + 1) << "] " << movies[i].getTitle()
             << "\t" << movies[i].getLanguage() << "\t" << movies[i].getDuration() << " min" << endl;
    }
}

// ---------------- F2: shows for a chosen movie ----------------

vector<Show*> showsForMovie(vector<Show>& shows, Movie* movie) {
    vector<Show*> result;
    for (int i = 0; i < (int)shows.size(); i++) {
        if (shows[i].getMovie() == movie) result.push_back(&shows[i]);
    }
    return result;
}

// ---------------- the full booking flow: F2 -> F3 -> F4 -> F5 -> F6 -> F7 ----------------

void bookFlow(vector<Movie>& movies, vector<Show>& shows, Customer* customer, BookingService& bookingService) {
    listMovies(movies);
    cout << "Choose movie: ";
    int m = readMenuChoice();
    if (m < 1 || m > (int)movies.size()) {
        cout << "  Invalid movie choice." << endl; // edge case 4
        return;
    }
    Movie* movie = &movies[m - 1];

    vector<Show*> movieShows = showsForMovie(shows, movie); // F2
    cout << endl;
    for (int i = 0; i < (int)movieShows.size(); i++) {
        cout << "  [" << (i + 1) << "] " << movieShows[i]->getScreen()->getDisplayName()
             << "\t" << movieShows[i]->getStartTime() << endl;
    }
    cout << "Choose show: ";
    int s = readMenuChoice();
    if (s < 1 || s > (int)movieShows.size()) {
        cout << "  Invalid show choice." << endl; // edge case 4
        return;
    }
    Show* show = movieShows[s - 1];

    cout << endl;
    show->displaySeats(); // F3

    cout << "Seats (e.g. A1,B2): ";
    string line;
    getline(cin, line);
    vector<string> seatNumbers = splitSeats(line);
    if (seatNumbers.empty()) {
        cout << "  No seats entered." << endl; // edge case 4
        return;
    }

    Booking* booking = bookingService.bookSeats(show, customer, seatNumbers); // F4 + F5
    if (booking == nullptr) {
        return; // rejection message already printed -- edge cases 1 & 4
    }

    for (int i = 0; i < (int)seatNumbers.size(); i++) {
        ShowSeat* ss = show->findShowSeat(seatNumbers[i]);
        cout << "  " << seatNumbers[i] << " " << ss->getSeat()->getTypeName()
             << " Rs." << ss->getSeat()->getPrice() << endl;
    }
    cout << "  TOTAL          Rs." << booking->getTotalAmount() << endl;

    cout << endl << "Pay by: 1.UPI  2.Card  3.Cash > ";
    int payChoice = readMenuChoice();

    Payment* payment = nullptr;
    if (payChoice == 1) {
        cout << "  Enter UPI id: ";
        string upi; getline(cin, upi);
        payment = new UpiPayment(upi, booking->getTotalAmount());
    } else if (payChoice == 2) {
        cout << "  Enter 16-digit card number: ";
        string card; getline(cin, card);
        payment = new CardPayment(card, booking->getTotalAmount());
    } else if (payChoice == 3) {
        cout << "  Enter cash given: ";
        double cash = 0;
        cin >> cash;
        if (cin.fail()) { cin.clear(); cash = -1; } // bad input -> guaranteed insufficient -> fails cleanly
        cin.ignore(10000, '\n');
        payment = new CashPayment(cash, booking->getTotalAmount());
    } else {
        cout << "  Invalid payment option. Booking not confirmed." << endl; // edge case 4
        booking->fail();
        return;
    }

    bookingService.makePayment(booking, payment); // F6 (+F7 on success)
    delete payment;
}

// ---------------- F8: cancel ----------------

void cancelFlow(BookingService& bookingService, Customer* customer) {
    cout << "Booking ID to cancel: ";
    string id; getline(cin, id);
    bookingService.cancelBooking(id, customer);
}

// ---------------- "My tickets" ----------------

void myTicketsFlow(BookingService& bookingService, Customer* customer) {
    vector<Booking*> mine = bookingService.getBookingsFor(customer);
    if (mine.empty()) {
        cout << "  You have no bookings yet." << endl;
        return;
    }
    TicketPrinter printer;
    for (int i = 0; i < (int)mine.size(); i++) {
        printer.printTicket(mine[i]);
    }
}

// ---------------- one-time setup: cinema, screens, seats, movies, shows ----------------

void setupCinema(Cinema& cinema, vector<Movie>& movies, vector<Show>& shows) {
    Screen screen1(1);
    screen1.addSeat(Seat("A1", SeatType::SILVER));
    screen1.addSeat(Seat("A2", SeatType::SILVER));
    screen1.addSeat(Seat("A3", SeatType::SILVER));
    screen1.addSeat(Seat("A4", SeatType::SILVER));
    screen1.addSeat(Seat("B1", SeatType::GOLD));
    screen1.addSeat(Seat("B2", SeatType::GOLD));
    screen1.addSeat(Seat("B3", SeatType::GOLD));
    screen1.addSeat(Seat("C1", SeatType::PLATINUM));
    screen1.addSeat(Seat("C2", SeatType::PLATINUM));

    Screen screen2(2);
    screen2.addSeat(Seat("A1", SeatType::SILVER));
    screen2.addSeat(Seat("A2", SeatType::SILVER));
    screen2.addSeat(Seat("A3", SeatType::SILVER));
    screen2.addSeat(Seat("A4", SeatType::SILVER));
    screen2.addSeat(Seat("B1", SeatType::GOLD));
    screen2.addSeat(Seat("B2", SeatType::GOLD));
    screen2.addSeat(Seat("B3", SeatType::GOLD));
    screen2.addSeat(Seat("C1", SeatType::PLATINUM));
    screen2.addSeat(Seat("C2", SeatType::PLATINUM));

    cinema.addScreen(screen1);
    cinema.addScreen(screen2);

    // Stable pointers -- no more screens are added after this point, so the
    // vector inside Cinema will not reallocate and invalidate these pointers.
    Screen* s1 = &cinema.getScreens()[0];
    Screen* s2 = &cinema.getScreens()[1];

    movies.push_back(Movie("3 Idiots", "Hindi", 170));
    movies.push_back(Movie("Interstellar", "English", 169));

    // Same reasoning: grab Movie* pointers only once all movies exist.
    Movie* m1 = &movies[0];
    Movie* m2 = &movies[1];

    shows.push_back(Show(m1, s1, "06:00 PM"));
    shows.push_back(Show(m1, s2, "09:00 PM"));
    shows.push_back(Show(m2, s1, "09:00 PM"));
    shows.push_back(Show(m2, s2, "06:00 PM"));
}

int main() {
    Cinema cinema("PVR Cinemas");
    vector<Movie> movies;
    vector<Show> shows;
    setupCinema(cinema, movies, shows);

    cout << "Enter your name (blank for Guest): ";
    string name; getline(cin, name);

    Customer customer; // default constructor -> "Guest" / "N/A"
    if (!name.empty()) {
        cout << "Enter your phone: ";
        string phone; getline(cin, phone);
        customer = Customer(name, phone); // the OTHER overloaded constructor
    }

    BookingService bookingService;

    while (true) {
        cout << endl << "===== MOVIE TICKET BOOKING =====" << endl;
        cout << "1. Movies   2. Book   3. Cancel   4. My tickets   0. Exit" << endl;
        cout << "Choose: ";
        int choice = readMenuChoice();

        if (choice == 1) {
            listMovies(movies); // F1
        } else if (choice == 2) {
            bookFlow(movies, shows, &customer, bookingService);
        } else if (choice == 3) {
            cancelFlow(bookingService, &customer); // F8
        } else if (choice == 4) {
            myTicketsFlow(bookingService, &customer);
        } else if (choice == 0) {
            cout << "Goodbye!" << endl;
            break;
        } else {
            cout << "  Invalid choice, try again." << endl; // edge case 4
        }
    }

    return 0;
}
