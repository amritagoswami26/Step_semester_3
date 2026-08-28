#include <bits/stdc++.h>
using namespace std;

class FeeAccount {
private:
    string regNo;
    double totalFee;
    double amountPaid;

public:
    // Constructor
    FeeAccount(string r, double fee) {
        regNo = r;
        totalFee = fee;
        amountPaid = 0;
    }

    void pay(double amount) {
        if (amount > 0) {
            amountPaid += amount;

            if (amountPaid > totalFee) {
                amountPaid = totalFee;
            }
        }
        else {
            cout << "Invalid payment amount" << endl;
        }
    }

    void payInTwoInstallments(double amount) {
        pay(amount / 2);
        pay(amount / 2);
    }

    double getDue() {
        return totalFee - amountPaid;
    }

    double effectiveDue(double scholarshipPercent) {
        return getDue() -
               (getDue() * scholarshipPercent / 100);
    }
};

int main() {
    FeeAccount accountA("RA231100301", 200000);
    FeeAccount accountB("RA231100302", 180000);

    // Account A pays Rs 120000 in two installments
    accountA.payInTwoInstallments(120000);

    cout << "Account A due: Rs "
         << accountA.getDue() << endl;

    // Account B gets 20% scholarship
    cout << "Account B effective due (20% scholarship): Rs "
         << accountB.effectiveDue(20) << endl;

    return 0;
}