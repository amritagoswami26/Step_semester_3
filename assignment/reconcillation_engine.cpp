#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
using namespace std;


// ---------------- SURGE FEE CALCULATOR ----------------

class SurgeFeeCalculator final {
private:
    const double minimumSurgePercent;

public:

    SurgeFeeCalculator(double minimumSurgePercent)
        : minimumSurgePercent(minimumSurgePercent) {
    }

    double calculateSurgeFee(double orderValue,
                             int delayMinutes) const {

        if (orderValue < 0 || delayMinutes < 0) {
            throw invalid_argument("Invalid input");
        }

        if (delayMinutes == 0) {
            return 0.0;
        }

        double surge = 0.0;

        // Minutes 1-5
        int firstTier = min(delayMinutes, 5);

        surge += firstTier * orderValue * 0.005;

        // Minutes 6-15
        if (delayMinutes > 5) {

            int secondTier = min(delayMinutes, 15) - 5;

            surge += secondTier * orderValue * 0.01;
        }

        // Minutes 16 onwards
        if (delayMinutes > 15) {

            int thirdTier = delayMinutes - 15;

            surge += thirdTier * orderValue * 0.02;
        }

        double minimumSurge =
            orderValue * minimumSurgePercent / 100.0;

        return max(surge, minimumSurge);
    }
};


// ---------------- DELIVERY ACCOUNT ----------------

class DeliveryAccount {
protected:
    string studentId;
    double orderValue;

    // Class-level state
    inline static int totalAccounts = 0;

public:

    // Full constructor
    DeliveryAccount(string studentId, double orderValue) {

        if (orderValue < 0) {
            throw invalid_argument("Invalid order value");
        }

        this->studentId = studentId;
        this->orderValue = orderValue;

        totalAccounts++;
    }

    // Provisional constructor
    DeliveryAccount(string studentId)
        : DeliveryAccount(studentId, 0.0) {
    }

    // final equivalent in C++:
    // prevent overriding by using final
    virtual double calculateSurgeFee(int delayMinutes) const final {

        SurgeFeeCalculator calculator(1.0);

        return calculator.calculateSurgeFee(
            orderValue,
            delayMinutes
        );
    }

    virtual void processAccount(double amount,
                                int delayMinutes) {

        double fee = calculateSurgeFee(delayMinutes);

        cout << "Regular Account: "
             << studentId
             << " | Amount: " << amount
             << " | Surge Fee: " << fee
             << endl;
    }

    virtual ~DeliveryAccount() {}
};


// ---------------- PREMIUM ACCOUNT ----------------

class PremiumAccount : public DeliveryAccount {
public:

    PremiumAccount(string studentId, double orderValue)
        : DeliveryAccount(studentId, orderValue) {
    }

    void processPremium(double amount, int delayMinutes) {

        double fee = calculateSurgeFee(delayMinutes);

        cout << "Premium Account: "
             << studentId
             << " | Amount: " << amount
             << " | Surge Fee: " << fee
             << endl;
    }
};


// ---------------- PROCESSOR ----------------

class ReconciliationEngine {
public:

    static void processBatch(
        vector<DeliveryAccount*> accounts,
        vector<double> amounts,
        vector<int> delayMinutesArray) {

        // If lengths don't match, process only matching indexes.
        int n = min(
            accounts.size(),
            min(amounts.size(), delayMinutesArray.size())
        );

        int processed = 0;
        int nullSkipped = 0;
        int premium = 0;
        int regular = 0;

        double grandTotal = 0.0;

        for (int i = 0; i < n; i++) {

            // Handle null safely
            if (accounts[i] == nullptr) {

                nullSkipped++;
                continue;
            }

            try {

                DeliveryAccount* account = accounts[i];

                double fee =
                    account->calculateSurgeFee(
                        delayMinutesArray[i]
                    );

                // Java instanceof equivalent
                PremiumAccount* premiumAccount =
                    dynamic_cast<PremiumAccount*>(account);

                if (premiumAccount != nullptr) {

                    premium++;

                    premiumAccount->processPremium(
                        amounts[i],
                        delayMinutesArray[i]
                    );
                }
                else {

                    regular++;

                    account->processAccount(
                        amounts[i],
                        delayMinutesArray[i]
                    );
                }

                grandTotal += fee;
                processed++;

            }
            catch (exception &e) {

                // Bad entry does not crash entire batch
                continue;
            }
        }

        cout << "\n--------------------------------" << endl;

        cout << processed
             << " processed | "
             << nullSkipped
             << " null skipped | "
             << premium
             << " premium | "
             << regular
             << " regular | "
             << "grand total surge fees = "
             << fixed << setprecision(2)
             << grandTotal
             << endl;
    }
};


// ---------------- MAIN ----------------

int main() {

    PremiumAccount premium1("STU001", 500);

    DeliveryAccount regular1("STU002", 300);

    vector<DeliveryAccount*> accounts = {
        &premium1,
        nullptr,
        &regular1
    };

    vector<double> amounts = {
        500,
        400,
        300
    };

    vector<int> delayMinutesArray = {
        10,
        5,
        0
    };

    ReconciliationEngine::processBatch(
        accounts,
        amounts,
        delayMinutesArray
    );

    return 0;
}