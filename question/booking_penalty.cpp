#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
using namespace std;

class BoardingPenaltyCalculator final {
private:
    const double minimumPenaltyPercent;

public:
    // Constructor
    BoardingPenaltyCalculator(double minimumPenaltyPercent)
        : minimumPenaltyPercent(minimumPenaltyPercent) {
    }

    // Calculate penalty
    double calculatePenalty(double ticketFare, int minutesLate) const {

        if (ticketFare < 0 || minutesLate < 0) {
            throw invalid_argument("Invalid input");
        }

        // No penalty if not late
        if (minutesLate == 0) {
            return 0.0;
        }

        double penalty = 0.0;

        // Minutes 1-5: 0.5% per minute
        int firstTier = min(minutesLate, 5);
        penalty += firstTier * ticketFare * 0.005;

        // Minutes 6-15: 1% per minute
        if (minutesLate > 5) {
            int secondTier = min(minutesLate, 15) - 5;
            penalty += secondTier * ticketFare * 0.01;
        }

        // Minutes 16 onwards: 2% per minute
        if (minutesLate > 15) {
            int thirdTier = minutesLate - 15;
            penalty += thirdTier * ticketFare * 0.02;
        }

        // Minimum penalty floor
        double minimumPenalty =
            ticketFare * minimumPenaltyPercent / 100.0;

        return max(penalty, minimumPenalty);
    }
};

int main() {

    BoardingPenaltyCalculator calculator(1.0);

    cout << fixed << setprecision(2);

    cout << "Penalty for 0 minutes: "
         << calculator.calculatePenalty(1000, 0) << endl;

    cout << "Penalty for 1 minute: "
         << calculator.calculatePenalty(1000, 1) << endl;

    cout << "Penalty for 16 minutes: "
         << calculator.calculatePenalty(1000, 16) << endl;

    return 0;
}