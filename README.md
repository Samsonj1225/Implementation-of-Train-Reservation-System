# Train-Reservation-System-using-C++

This project is a Train Reservation System developed in C++. It simulates a railway ticket booking system, allowing users to manage trains, coaches, reservations, and cancellations. The system supports Tatkal, RAC, and Waiting List bookings and allows passengers to choose food and drink preferences during reservation.

The system is designed to run in a terminal and provides an interactive, menu-driven interface suitable for learning and demonstration purposes.

### 1. Features of the Project

- Add new trains with multiple coaches and seats
- Reserve seats with passenger details
- Food and drink ordering during booking
- Support for:
  - Confirmed bookings
  - Tatkal bookings (with fare markup)
  - RAC and Waiting List (with auto-confirmation)
- Cancel reservations by PNR
- Check seat availability by train and coach
- View all reservations with complete details

### 2. Setup and Compilation

Ensure you have a C++ compiler (like g++) installed.

g++ -o train_reservation train_reservation.cpp

### 3. Menu Options


     TRAIN RESERVATION SYSTEM

1. Add Train
2. Reserve Seat
3. Display All Trains
4. Display Reservations
5. Cancel Reservation
6. Check Seat Availability
7. Auto confirm RAC and Waiting List Reservations
8. Exit

### 4. Reservation Details

While booking, the user can:

- Enter personal details (name, age)
- Choose food (Veg/Non-Veg options) and specific item
- Choose drinks (Coke, Sprite, Fanta, Lemonade)
- Opt for Tatkal (charges 20% extra)
- Get added to RAC or Waiting List if seats are full

Example Output:

Reservation successful!
PNR: PNR123456
Train: Express101
Coach: C1
Seat: 1
Passenger: Alice
Age: 25
Food: Paneer Butter Masala
Drink: Coke
Fare: 500
Status: Confirmed

### 5. Auto Confirmation of RAC/Waiting

When a confirmed reservation is canceled, the system automatically:

- Promotes RAC reservations to Confirmed
- Moves Waiting List passengers to RAC or Confirmed (if seats are available)

### 6. Data Structures Used

- Train: Stores train details and list of Coach
- Coach: Stores coach info, fare, and list of Seat
- Seat: Stores reservation status and passenger info
- Reservation: Keeps track of booking details and status

