#include <iostream>
#include <vector>
using namespace std;

class EventTicket {
protected:
    double basePrice;
    double amountPaid;
    vector<double> lateFeeHistory;

public:
    EventTicket(double price) {
        basePrice = price;
        amountPaid = 0;
    }

    void pay(double amount) {
        amountPaid += amount;
    }

    double getBalanceDue() {
        return basePrice - amountPaid;
    }

protected:
    virtual void applyLateFee(double amount) {
        basePrice += amount;
        lateFeeHistory.push_back(amount);
    }

public:
    vector<double> getLateFeeHistory() {
        // Returns a copy
        return lateFeeHistory;
    }
};

class WorkshopTicket : public EventTicket {
public:
    WorkshopTicket(double price)
        : EventTicket(price) {}

    void applyLateFee(double amount) override {
        EventTicket::applyLateFee(amount * 2);
    }
};

int main() {
    WorkshopTicket w(1200);

    w.pay(1200);

    w.applyLateFee(100);

    cout << w.getBalanceDue() << endl;

    vector<double> history = w.getLateFeeHistory();

    history[0] = 999;

    vector<double> actual = w.getLateFeeHistory();

    cout << actual[0] << endl;

    return 0;
}