#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Seat {
    int seatNumber;
    bool reserved;
    string passengerName;
    int passengerAge;
    string foodChoice;
    string drinkChoice;
};

struct Coach {
    string coachName;
    float fare;
    vector<Seat> seats;
};

struct Train {
    string trainName;
    string source;
    string destination;
    string departureTime;
    vector<Coach> coaches;
};

struct Reservation {
    string pnr;
    string trainName;
    string coachName;
    int seatNumber;
    string passengerName;
    int passengerAge;
    float fare;
    string foodChoice;
    string drinkChoice;
    string status; // Confirmed / Tatkal / RAC / Waiting
};

vector<Train> trains;
vector<Reservation> confirmedReservations;
vector<Reservation> tatkalReservations;
vector<Reservation> racList;
vector<Reservation> waitingList;

string generatePNR() {
    string pnr = "PNR";
    for (int i = 0; i < 6; ++i)
        pnr += to_string(rand() % 10);
    return pnr;
}

void displayMenu() {
    cout << "\n==============================\n";
    cout << "     TRAIN RESERVATION SYSTEM\n";
    cout << "==============================\n";
    cout << "1. Add Train\n";
    cout << "2. Reserve Seat\n";
    cout << "3. Display All Trains\n";
    cout << "4. Display Reservations\n";
    cout << "5. Cancel Reservation\n";
    cout << "6. Check Seat Availability\n";
    cout << "7. Auto confirm RAC and Waiting List Reservations\n";
    cout << "8. Exit\n";
    cout << "Enter your choice: ";
}

void addTrain() {
    Train t;
    cout << "\nEnter Train Name: ";
    cin >> t.trainName;
    cout << "Enter Source: ";
    cin >> t.source;
    cout << "Enter Destination: ";
    cin >> t.destination;
    cout << "Enter Departure Time: ";
    cin >> t.departureTime;
    int numCoaches;
    cout << "Enter number of coaches: ";
    cin >> numCoaches;
    for (int i = 0; i < numCoaches; i++) {
        Coach c;
        cout << "Enter Coach Name: ";
        cin >> c.coachName;
        cout << "Enter Fare: ";
        cin >> c.fare;
        int numSeats;
        cout << "Enter number of seats: ";
        cin >> numSeats;
        for (int j = 0; j < numSeats; j++) {
            Seat s;
            s.seatNumber = j + 1;
            s.reserved = false;
            c.seats.push_back(s);
        }
        t.coaches.push_back(c);
    }
    trains.push_back(t);
    cout << "Train added successfully!\n";
}

void displayAllTrains() {
    for (const auto& t : trains) {
        cout << "\nTrain: " << t.trainName << " | From: " << t.source << " To: " << t.destination
             << " | Departs at: " << t.departureTime << endl;
        for (const auto& c : t.coaches) {
            int available = 0;
            for (const auto& s : c.seats)
                if (!s.reserved) available++;
            cout << "Coach: " << c.coachName << " | Fare: " << c.fare << " | Available Seats: " << available << endl;
        }
    }
}

void reserveSeat() {
    string trainName, coachName;
    cout << "\nEnter Train Name: ";
    cin >> trainName;
    cout << "Enter Coach Name: ";
    cin >> coachName;
    Train* selectedTrain = nullptr;
    Coach* selectedCoach = nullptr;

    for (auto& t : trains) {
        if (t.trainName == trainName) {
            selectedTrain = &t;
            for (auto& c : t.coaches) {
                if (c.coachName == coachName) {
                    selectedCoach = &c;
                    break;
                }
            }
            break;
        }
    }

    if (!selectedTrain || !selectedCoach) {
        cout << "Invalid train or coach name!\n";
        return;
    }

    string name, food, drink;
    int age;
    cout << "Enter Passenger Name: ";
    cin.ignore(); getline(cin, name);
    cout << "Enter Age: ";
    cin >> age;

    // Food ordering part
    string foodPreference;
    cout << "Would you like to order food? (yes/no): ";
    string foodOrder;
    cin >> foodOrder;

    vector<string> vegFoods = {"Paneer Butter Masala", "Dal Makhani", "Mixed Veg Curry", "Chole Bhature"};
    vector<string> nonVegFoods = {"Chicken Tikka", "Chicken Biryani", "Butter Chicken", "Mutton Rogan Josh"};

    if (foodOrder == "yes" || foodOrder == "Yes") {
        cout << "Enter food preference (veg/non-veg): ";
        cin >> foodPreference;
        if (foodPreference == "veg" || foodPreference == "Veg") {
            cout << "Available veg food options: ";
            for (auto& f : vegFoods) cout << f << ", ";
            cout << "\nEnter your choice exactly as above: ";
            cin.ignore();
            getline(cin, food);
        } else if (foodPreference == "non-veg" || foodPreference == "Non-veg" || foodPreference == "nonveg") {
            cout << "Available non-veg food options: ";
            for (auto& f : nonVegFoods) cout << f << ", ";
            cout << "\nEnter your choice exactly as above: ";
            cin.ignore();
            getline(cin, food);
        } else {
            food = "No Food";
        }
    } else {
        food = "No Food";
        cin.ignore();
    }

    // Drink ordering part
    cout << "Would you like to order a drink? (yes/no): ";
    string drinkOrder;
    cin >> drinkOrder;
    vector<string> drinks = {"Coke", "Sprite", "Fanta", "Lemonade"};
    if (drinkOrder == "yes" || drinkOrder == "Yes") {
        cout << "Available drink options: ";
        for (auto& d : drinks) cout << d << ", ";
        cout << "\nEnter your drink choice exactly as above: ";
        cin.ignore();
        getline(cin, drink);
    } else {
        drink = "No Drink";
        cin.ignore();
    }

    Reservation r;
    r.pnr = generatePNR();
    r.passengerName = name;
    r.passengerAge = age;
    r.foodChoice = food;
    r.drinkChoice = drink;
    r.trainName = trainName;
    r.coachName = coachName;

    bool seatFound = false;
    for (auto& seat : selectedCoach->seats) {
        if (!seat.reserved) {
            seat.reserved = true;
            seat.passengerName = name;
            seat.passengerAge = age;
            seat.foodChoice = food;
            seat.drinkChoice = drink;

            r.seatNumber = seat.seatNumber;

            if (age < 12 || age > 60)
                r.fare = selectedCoach->fare * 0.5;
            else
                r.fare = selectedCoach->fare;

            cout << "Is this a Tatkal reservation? (y/n): ";
            char tatkal;
            cin >> tatkal;
            if (tatkal == 'y' || tatkal == 'Y') {
                r.fare *= 1.2;
                r.status = "Tatkal";
                tatkalReservations.push_back(r);
            } else {
                r.status = "Confirmed";
                confirmedReservations.push_back(r);
            }

            cout << "Reservation successful! \n"
                 << "PNR: " << r.pnr << "\n"
                 << "Train: " << r.trainName << "\n"
                 << "Coach: " << r.coachName << "\n"
                 << "Seat: " << r.seatNumber << "\n"
                 << "Passenger: " << r.passengerName << "\n"
                 << "Age: " << r.passengerAge << "\n"
                 << "Food: " << r.foodChoice << "\n"
                 << "Drink: " << r.drinkChoice << "\n"
                 << "Fare: " << r.fare << "\n"
                 << "Status: " << r.status << "\n";
            seatFound = true;
            break;
        }
    }

    if (!seatFound) {
        r.fare = selectedCoach->fare;
        r.seatNumber = 0;
        if (racList.size() < 5) {
            r.status = "RAC";
            racList.push_back(r);
            cout << "No seats available. Added to RAC. PNR: " << r.pnr << endl;
        } else {
            r.status = "Waiting";
            waitingList.push_back(r);
            cout << "No seats available. Added to Waiting List. PNR: " << r.pnr << endl;
        }
    }
}

void displayReservations(const vector<Reservation>& resList, const string& title) {
    cout << "\n" << title << ":\n";
    if (resList.empty()) {
        cout << "No reservations.\n";
        return;
    }
    for (const auto& r : resList) {
        cout << "PNR: " << r.pnr << ", Train: " << r.trainName << ", Coach: " << r.coachName
             << ", Seat: " << (r.seatNumber == 0 ? "N/A" : to_string(r.seatNumber)) << ", Name: " << r.passengerName
             << ", Age: " << r.passengerAge << ", Fare: " << r.fare << ", Food: " << r.foodChoice
             << ", Drink: " << r.drinkChoice << ", Status: " << r.status << endl;
    }
}

void cancelReservation() {
    string pnr;
    cout << "\nEnter PNR to cancel: ";
    cin >> pnr;
    for (auto it = confirmedReservations.begin(); it != confirmedReservations.end(); ++it) {
        if (it->pnr == pnr) {
            for (auto& t : trains) {
                if (t.trainName == it->trainName) {
                    for (auto& c : t.coaches) {
                        if (c.coachName == it->coachName) {
                            for (auto& s : c.seats) {
                                if (s.seatNumber == it->seatNumber) {
                                    s.reserved = false;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            confirmedReservations.erase(it);
            cout << "Reservation canceled for PNR: " << pnr << endl;
            return;
        }
    }
    cout << "Reservation not found for PNR: " << pnr << endl;
}

void checkSeatAvailability() {
    string trainName, coachName;
    cout << "\nEnter Train Name: ";
    cin >> trainName;
    cout << "Enter Coach Name: ";
    cin >> coachName;
    for (const auto& t : trains) {
        if (t.trainName == trainName) {
            for (const auto& c : t.coaches) {
                if (c.coachName == coachName) {
                    cout << "Available seats: ";
                    bool anyAvailable = false;
                    for (const auto& s : c.seats) {
                        if (!s.reserved) {
                            cout << s.seatNumber << " ";
                            anyAvailable = true;
                        }
                    }
                    if (!anyAvailable)
                        cout << "None";
                    cout << endl;
                    return;
                }
            }
        }
    }
    cout << "Train or coach not found.\n";
}

void autoConfirmRACandWaitingList() {
    // Confirm RAC passengers
    for (auto it = racList.begin(); it != racList.end();) {
        bool confirmed = false;
        for (auto& t : trains) {
            if (t.trainName == it->trainName) {
                for (auto& c : t.coaches) {
                    if (c.coachName == it->coachName) {
                        for (auto& s : c.seats) {
                            if (!s.reserved) {
                                s.reserved = true;
                                s.passengerName = it->passengerName;
                                s.passengerAge = it->passengerAge;
                                s.foodChoice = it->foodChoice;
                                s.drinkChoice = it->drinkChoice;
                                it->seatNumber = s.seatNumber;
                                it->status = "Confirmed";
                                confirmedReservations.push_back(*it);
                                it = racList.erase(it);
                                confirmed = true;
                                break;
                            }
                        }
                    }
                    if (confirmed) break;
                }
            }
            if (confirmed) break;
        }
        if (!confirmed) ++it;
    }

    // Confirm Waiting list passengers
    for (auto it = waitingList.begin(); it != waitingList.end();) {
        bool confirmed = false;
        for (auto& t : trains) {
            if (t.trainName == it->trainName) {
                for (auto& c : t.coaches) {
                    if (c.coachName == it->coachName) {
                        for (auto& s : c.seats) {
                            if (!s.reserved) {
                                s.reserved = true;
                                s.passengerName = it->passengerName;
                                s.passengerAge = it->passengerAge;
                                s.foodChoice = it->foodChoice;
                                s.drinkChoice = it->drinkChoice;
                                it->seatNumber = s.seatNumber;
                                it->status = "Confirmed";
                                confirmedReservations.push_back(*it);
                                it = waitingList.erase(it);
                                confirmed = true;
                                break;
                            }
                        }
                    }
                    if (confirmed) break;
                }
            }
            if (confirmed) break;
        }
        if (!confirmed) ++it;
    }

    cout << "Auto confirmation of RAC and Waiting List reservations done.\n";
}

int main() {
    srand(time(0));
    int choice;
    do {
        displayMenu();
        cin >> choice;
        switch (choice) {
            case 1: addTrain(); break;
            case 2: reserveSeat(); break;
            case 3: displayAllTrains(); break;
            case 4:
                displayReservations(confirmedReservations, "Confirmed Reservations");
                displayReservations(tatkalReservations, "Tatkal Reservations");
                displayReservations(racList, "RAC List");
                displayReservations(waitingList, "Waiting List");
                break;
            case 5: cancelReservation(); break;
            case 6: checkSeatAvailability(); break;
            case 7: autoConfirmRACandWaitingList(); break;
            case 8: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 8);
    return 0;
}
