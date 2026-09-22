#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <stdexcept>
#include <cctype>

using namespace std;

class BusTicket {
private:
    string passengerName;
    string destination;
    bool checkedIn;

public:

    // Parameterized constructor only
    BusTicket(string passengerName, string destination) {

        // Check passenger name
        if (passengerName.empty())
            throw invalid_argument("Invalid passenger name");

        // Check whitespace-only name
        bool nameHasCharacter = false;

        for (char c : passengerName) {
            if (!isspace(c)) {
                nameHasCharacter = true;
                break;
            }
        }

        if (!nameHasCharacter)
            throw invalid_argument("Invalid passenger name");

        // Name should contain only letters and spaces
        for (char c : passengerName) {
            if (!isalpha(c) && !isspace(c))
                throw invalid_argument("Invalid passenger name");
        }

        // Destination validation
        if (destination.empty())
            throw invalid_argument("Invalid destination");

        bool destinationHasCharacter = false;

        for (char c : destination) {
            if (!isspace(c)) {
                destinationHasCharacter = true;
                break;
            }
        }

        if (!destinationHasCharacter)
            throw invalid_argument("Invalid destination");

        this->passengerName = passengerName;
        this->destination = destination;
        this->checkedIn = false;
    }

    void markCheckedIn() {

        // Idempotent state change
        if (!checkedIn) {
            checkedIn = true;
        }
    }

    string getKey() const {
        return passengerName + "|" + destination;
    }
};


class BookingProcessor {
public:

    static void processBatch(
        vector<vector<string>> rawBookings) {

        set<string> acceptedBookings;

        int valid = 0;
        int rejected = 0;
        int duplicates = 0;

        for (auto &booking : rawBookings) {

            string name = booking[0];
            string destination = booking[1];

            try {

                BusTicket ticket(name, destination);

                string key = ticket.getKey();

                // Duplicate
                if (acceptedBookings.count(key)) {
                    duplicates++;
                }
                else {
                    acceptedBookings.insert(key);
                    valid++;
                }

            }
            catch (exception &e) {
                rejected++;
            }
        }

        cout << "Valid: " << valid
             << " | Rejected: " << rejected
             << " | Duplicates skipped: "
             << duplicates << endl;
    }
};


int main() {

    vector<vector<string>> bookings = {
        {"Divya", "Chennai"},
        {"", "Bangalore"},
        {"Ravi123", "Pune"},
        {"Divya", "Chennai"},
        {" ", " "}
    };

    BookingProcessor::processBatch(bookings);

    return 0;
}