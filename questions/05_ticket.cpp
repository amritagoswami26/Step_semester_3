#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

class EventTicket {
protected:
    double basePrice;
    double amountPaid;

private:
    static int counter;
    const string ticketId;

public:
    EventTicket(double price)
        : ticketId("TCK-" + to_string(1000 + ++counter)) {
        
        basePrice = price;
        amountPaid = 0;
    }

    void pay(double amount) {
        amountPaid += amount;
    }

    void pay(double amount, string mode) {
        cout << "Payment Mode: " << mode << endl;
        pay(amount);
    }

    double getBalanceDue() {
        return basePrice - amountPaid;
    }

    string getTicketId() {
        return ticketId;
    }

    static bool isValidPromoCode(string code) {

        if (code.length() != 5)
            return false;

        if (code[0] != 'F')
            return false;

        if (!isdigit(code[1]) ||
            !isdigit(code[2]) ||
            !isdigit(code[3]))
            return false;

        if (!isupper(code[4]))
            return false;

        return true;
    }

    static int getTicketsIssued() {
        return counter;
    }

    virtual ~EventTicket() {}
};

int EventTicket::counter = 0;


class GroupTicket : public EventTicket {
    int groupSize;

public:
    GroupTicket(double price, int groupSize)
        : EventTicket(price) {
        this->groupSize = groupSize;
    }
};


string processNightlySettlement(vector<EventTicket*> tickets) {

    int processed = 0;
    int nullSkipped = 0;
    int group = 0;
    int individual = 0;

    for (EventTicket* ticket : tickets) {

        if (ticket == nullptr) {
            nullSkipped++;
            continue;
        }

        processed++;

        GroupTicket* g =
            dynamic_cast<GroupTicket*>(ticket);

        if (g != nullptr)
            group++;
        else
            individual++;
    }

    return to_string(processed) + " processed | " +
           to_string(nullSkipped) + " null skipped | " +
           to_string(group) + " group | " +
           to_string(individual) + " individual";
}


int main() {

    EventTicket t1(500);

    cout << t1.getTicketId() << endl;
    cout << EventTicket::getTicketsIssued() << endl;

    cout << EventTicket::isValidPromoCode("F123A") << endl;
    cout << EventTicket::isValidPromoCode("F12A") << endl;
    cout << EventTicket::isValidPromoCode("X123A") << endl;

    t1.pay(200);
    t1.pay(200, "UPI");

    cout << t1.getBalanceDue() << endl;

    GroupTicket g(2000, 5);

    vector<EventTicket*> tickets = {
        &g,
        nullptr,
        &t1
    };

    cout << processNightlySettlement(tickets) << endl;

    return 0;
}