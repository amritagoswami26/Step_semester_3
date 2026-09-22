#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class EventTicket {
protected:
    double basePrice;

public:
    EventTicket(double price) {
        basePrice = price;
    }

    virtual string printTicket() {
        return "Standard | Balance: " + to_string(basePrice);
    }

    virtual ~EventTicket() {}
};

class WorkshopTicket : public EventTicket {
    string track;

public:
    WorkshopTicket(double price, string track)
        : EventTicket(price) {
        this->track = track;
    }

    string printTicket() override {
        return "Workshop | Track: " + track +
               " | Balance: " + to_string(basePrice);
    }

    string getTrack() {
        return track;
    }
};

string batchPrint(vector<EventTicket*> tickets) {
    stringstream report;

    for (EventTicket* ticket : tickets) {

        report << ticket->printTicket();

        WorkshopTicket* workshop =
            dynamic_cast<WorkshopTicket*>(ticket);

        if (workshop != nullptr) {
            report << " [Track via downcast: "
                   << workshop->getTrack() << "]";
        }

        report << " | ";
    }

    return report.str();
}

int main() {
    EventTicket e(500);
    WorkshopTicket w(1200, "AI/ML");

    vector<EventTicket*> tickets = {&e, &w};

    cout << batchPrint(tickets) << endl;

    return 0;
}