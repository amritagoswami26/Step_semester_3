#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
using namespace std;

class SurgeFeeCalculator final {
private:
    const double minimumSurgePercent;

public:

    // Constructor
    SurgeFeeCalculator(double minimumSurgePercent)
        : minimumSurgePercent(minimumSurgePercent) {
    }

    // const method = calculation rule cannot modify object
    double calculateSurgeFee(double orderValue, int delayMinutes) const {

        if (orderValue < 0 || delayMinutes < 0) {
            throw invalid_argument("Invalid input");
        }

        // No delay means no surge fee
        if (delayMinutes == 0) {
            return 0.0;
        }

        double surge = 0.0;

        // Minutes 1-5 → 0.5% per minute
        int firstTier = min(delayMinutes, 5);

        surge += firstTier * orderValue * 0.005;

        // Minutes 6-15 → 1% per minute
        if (delayMinutes > 5) {

            int secondTier = min(delayMinutes, 15) - 5;

            surge += secondTier * orderValue * 0.01;
        }

        // Minutes 16 onwards → 2% per minute
        if (delayMinutes > 15) {

            int thirdTier = delayMinutes - 15;

            surge += thirdTier * orderValue * 0.02;
        }

        // Minimum surge floor
        double minimumSurge =
            orderValue * minimumSurgePercent / 100.0;

        return max(surge, minimumSurge);
    }
};

int main() {

    SurgeFeeCalculator calculator(1.0);

    cout << fixed << setprecision(1);

    cout << "Delay 0: Rs "
         << calculator.calculateSurgeFee(500, 0) << endl;

    cout << "Delay 1: Rs "
         << calculator.calculateSurgeFee(500, 1) << endl;

    cout << "Delay 16: Rs "
         << calculator.calculateSurgeFee(500, 16) << endl;

    return 0;
}