#include <iostream>
#include <string>
#include <vector>
using namespace std;

class RaceEntry {
protected:
    string bibNumber;
    double entryFee;
    double amountPaid;

private:
    vector<double> lateFeeHistory;

public:
    RaceEntry(string bibNumber, double entryFee) {
        this->bibNumber = bibNumber;
        this->entryFee = entryFee;
        amountPaid = 0;
    }

    void pay(double amount) {
        amountPaid += amount;
    }

    virtual double getBalanceDue() {
        return entryFee - amountPaid;
    }

protected:
    virtual void applyLateFee(double amount) {
        entryFee += amount;
        lateFeeHistory.push_back(amount);
    }

public:
    vector<double> getLateFeeHistory() {
        // Defensive copy
        return lateFeeHistory;
    }
};

class RunnerEntry : public RaceEntry {
private:
    string category;

public:
    RunnerEntry(string bibNumber, double entryFee, string category)
        : RaceEntry(bibNumber, entryFee) {
        this->category = category;
    }

    void applyLateFee(double amount) override {
        RaceEntry::applyLateFee(amount * 2);
    }

    // Public wrapper because applyLateFee is protected
    void addLateFee(double amount) {
        applyLateFee(amount);
    }
};

int main() {
    RunnerEntry r("BIB2001", 80, "Open 10K");

    r.pay(30);

    r.addLateFee(20);

    cout << r.getBalanceDue() << endl;

    vector<double> history = r.getLateFeeHistory();

    history[0] = 999;

    vector<double> actualHistory = r.getLateFeeHistory();

    cout << actualHistory[0] << endl;

    return 0;
}