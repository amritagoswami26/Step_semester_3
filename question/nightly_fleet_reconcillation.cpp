#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

using namespace std;


class BoardingPenaltyCalculator final {
private:
    const double minimumPenaltyPercent;

public:

    BoardingPenaltyCalculator(
        double minimumPenaltyPercent)
        : minimumPenaltyPercent(
              minimumPenaltyPercent) {
    }


    double calculatePenalty(
        double ticketFare,
        int minutesLate) const {

        if (ticketFare < 0 ||
            minutesLate < 0) {

            throw invalid_argument(
                "Invalid input"
            );
        }


        if (minutesLate == 0)
            return 0.0;


        double penalty = 0.0;


        // Minutes 1-5
        int firstTier =
            min(minutesLate, 5);

        penalty +=
            firstTier *
            ticketFare *
            0.005;


        // Minutes 6-15
        if (minutesLate > 5) {

            int secondTier =
                min(minutesLate, 15) - 5;

            penalty +=
                secondTier *
                ticketFare *
                0.01;
        }


        // Minutes 16+
        if (minutesLate > 15) {

            int thirdTier =
                minutesLate - 15;

            penalty +=
                thirdTier *
                ticketFare *
                0.02;
        }


        double minimumPenalty =
            ticketFare *
            minimumPenaltyPercent /
            100.0;


        return max(
            penalty,
            minimumPenalty
        );
    }
};


class BusTicketAccount {
protected:
    string bookingId;
    double ticketFare;

    static int totalAccounts;

public:

    // Static block equivalent:
    // static initialization is handled below
    BusTicketAccount(
        string bookingId,
        double ticketFare) {

        if (ticketFare < 0) {
            throw invalid_argument(
                "Invalid ticket fare"
            );
        }

        this->bookingId = bookingId;
        this->ticketFare = ticketFare;

        totalAccounts++;
    }


    // Provisional constructor
    BusTicketAccount(string bookingId)
        : BusTicketAccount(
              bookingId,
              0.0) {
    }


    virtual double calculatePenalty(
        int minutesLate) const {

        BoardingPenaltyCalculator calculator(
            1.0
        );

        return calculator.calculatePenalty(
            ticketFare,
            minutesLate
        );
    }


    virtual void processAccount(
        double amount,
        int minutesLate) {

        double penalty =
            calculatePenalty(minutesLate);

        cout << "Regular account "
             << bookingId
             << " | Amount: "
             << amount
             << " | Penalty: "
             << penalty
             << endl;
    }


    virtual ~BusTicketAccount() {}
};


// Static class-level state
int BusTicketAccount::totalAccounts = 0;


class SleeperBusTicketAccount
    : public BusTicketAccount {

public:

    SleeperBusTicketAccount(
        string bookingId,
        double ticketFare)
        : BusTicketAccount(
              bookingId,
              ticketFare) {
    }


    void processAccount(
        double amount,
        int minutesLate) override {

        double penalty =
            calculatePenalty(minutesLate);

        cout << "Sleeper account "
             << bookingId
             << " | Amount: "
             << amount
             << " | Penalty: "
             << penalty
             << endl;
    }
};


class FleetProcessor {
public:

    static void processBatch(
        vector<BusTicketAccount*> accounts,
        vector<double> amounts,
        vector<int> minutesLateArray) {

        // Mismatched arrays: process only
        // the common valid range
        int n = min(
            accounts.size(),
            min(
                amounts.size(),
                minutesLateArray.size()
            )
        );


        int processed = 0;
        int nullSkipped = 0;
        int sleeper = 0;
        int regular = 0;

        double grandTotalPenalty = 0.0;


        for (int i = 0; i < n; i++) {

            BusTicketAccount* account =
                accounts[i];


            if (account == nullptr) {

                nullSkipped++;
                continue;
            }


            try {

                double penalty =
                    account->calculatePenalty(
                        minutesLateArray[i]
                    );

                account->processAccount(
                    amounts[i],
                    minutesLateArray[i]
                );


                grandTotalPenalty += penalty;

                processed++;


                // instanceof equivalent
                if (dynamic_cast<
                        SleeperBusTicketAccount*
                    >(account) != nullptr) {

                    sleeper++;
                }
                else {

                    regular++;
                }
            }

            catch (exception &e) {

                // Bad individual entry does not
                // crash the entire batch
                continue;
            }
        }


        cout << processed
             << " processed | "
             << nullSkipped
             << " null skipped | "
             << sleeper
             << " sleeper | "
             << regular
             << " regular | grand total penalties = "
             << fixed
             << setprecision(2)
             << grandTotalPenalty
             << endl;
    }
};


int main() {

    SleeperBusTicketAccount sleeper(
        "BK001",
        2000
    );


    BusTicketAccount regular(
        "BK002",
        1200
    );


    vector<BusTicketAccount*> accounts = {

        &sleeper,

        nullptr,

        &regular
    };


    vector<double> amounts = {

        1200,
        900,
        700
    };


    vector<int> minutesLate = {

        10,
        5,
        0
    };


    FleetProcessor::processBatch(
        accounts,
        amounts,
        minutesLate
    );


    return 0;
}