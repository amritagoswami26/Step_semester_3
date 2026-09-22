#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

class EventTicket {
protected:
    string attendeeId;
    double basePrice;
    double amountPaid;

public:
    EventTicket(string attendeeId, double basePrice) {
        if (attendeeId.length() < 4) {
            throw invalid_argument("Invalid attendee ID");
        }

        bool onlySpaces = true;
        for (char c : attendeeId) {
            if (!isspace(c)) {
                onlySpaces = false;
                break;
            }
        }

        if (onlySpaces) {
            throw invalid_argument("Invalid attendee ID");
        }

        this->attendeeId = attendeeId;
        this->basePrice = basePrice;
        amountPaid = 0;
    }

    virtual void pay(double amount) {
        amountPaid += amount;
    }

    virtual double getBalanceDue() {
        return basePrice - amountPaid;
    }

    virtual ~EventTicket() {}

    static string registerBatch(vector<string> attendeeIds, double basePrice) {
        int registered = 0;
        int rejected = 0;

        for (string id : attendeeIds) {
            try {
                EventTicket t(id, basePrice);
                registered++;
            }
            catch (invalid_argument&) {
                rejected++;
            }
        }

        return "Registered: " + to_string(registered) +
               " | Rejected: " + to_string(rejected);
    }
};

class WorkshopTicket : public EventTicket {
    string track;

public:
    WorkshopTicket(string attendeeId, double basePrice, string track)
        : EventTicket(attendeeId, basePrice) {
        this->track = track;
    }
};

int main() {
    try {
        EventTicket t("STU1", 500);
        t.pay(200);

        cout << t.getBalanceDue() << endl;

        WorkshopTicket w("STU2", 1200, "AI/ML");
        w.pay(500);

        cout << w.getBalanceDue() << endl;

        vector<string> ids = {"STU1", "ST1", "STU2", " ", "STU3"};

        cout << EventTicket::registerBatch(ids, 500) << endl;
    }
    catch (exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}