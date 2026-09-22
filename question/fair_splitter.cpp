#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <cmath>

using namespace std;

class FareSplitter {
private:
    string tripId;
    double totalFare;
    int passengerCount;

public:

    // Main constructor
    FareSplitter(string tripId,
                 double totalFare,
                 int passengerCount) {

        if (totalFare < 0)
            throw invalid_argument("Negative fare");

        if (passengerCount <= 0)
            throw invalid_argument("Invalid passenger count");

        this->tripId = tripId;
        this->totalFare = totalFare;
        this->passengerCount = passengerCount;
    }


    // Constructor chaining
    FareSplitter(string tripId, double totalFare)
        : FareSplitter(tripId, totalFare, 1) {
    }


    // Provisional constructor
    FareSplitter(string tripId)
        : FareSplitter(tripId, 0.0, 2) {
    }


    vector<double> fareBreakdown() {

        vector<double> result(passengerCount, 0.0);

        if (totalFare == 0)
            return result;

        // Work in paise to avoid floating-point
        // remainder problems
        long long totalPaise =
            llround(totalFare * 100);

        long long base =
            totalPaise / passengerCount;

        long long remainder =
            totalPaise % passengerCount;

        for (int i = 0; i < passengerCount; i++) {

            result[i] = base / 100.0;
        }

        // Extra paisa goes to the last shares
        for (int i = passengerCount - remainder;
             i < passengerCount;
             i++) {

            result[i] += 0.01;
        }

        return result;
    }


    bool isConfirmationOverdue(
        int confirmed,
        int expected) {

        return confirmed < expected;
    }
};


int main() {

    FareSplitter f(
        "TRIP001",
        100000,
        3
    );

    vector<double> result =
        f.fareBreakdown();

    cout << fixed << setprecision(2);

    for (double x : result)
        cout << x << " ";

    cout << endl;


    FareSplitter provisional("TRIP003");

    vector<double> result2 =
        provisional.fareBreakdown();

    for (double x : result2)
        cout << x << " ";

    cout << endl;

    return 0;
}