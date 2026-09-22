#include <iostream>
#include <string>
#include <vector>
using namespace std;

class EventTicket {
protected:
    string attendeeId;
    double basePrice;
    double amountPaid;

public:
    EventTicket(string id, double price) {
        attendeeId = id;
        basePrice = price;
        amountPaid = 0;
    }

    virtual double getBalanceDue() {
        return basePrice - amountPaid;
    }

    virtual void printTicket() {
        cout << "Standard Event Ticket | Balance Due: "
             << getBalanceDue() << endl;
    }

    virtual ~EventTicket() {}
};

class WorkshopTicket : public EventTicket {
protected:
    string track;

public:
    WorkshopTicket(string id, double price, string track)
        : EventTicket(id, price) {
        this->track = track;
    }

    void printTicket() override {
        cout << "Workshop Ticket | Track: " << track
             << " | Balance Due: " << getBalanceDue() << endl;
    }
};

class PremiumWorkshopTicket : public WorkshopTicket {
    double kitFee;

public:
    PremiumWorkshopTicket(string id, double price,
                          string track, double kitFee)
        : WorkshopTicket(id, price, track) {
        this->kitFee = kitFee;
    }

    void printTicket() override {
        cout << "Premium Workshop Ticket | Track: "
             << track << " | Kit Fee: " << kitFee
             << " | Balance Due: " << getBalanceDue() << endl;
    }
};

class HackathonTicket : public EventTicket {
    string teamName;

public:
    HackathonTicket(string id, double price, string teamName)
        : EventTicket(id, price) {
        this->teamName = teamName;
    }

    void printTicket() override {
        cout << "Hackathon Ticket | Team: " << teamName
             << " | Balance Due: " << getBalanceDue() << endl;
    }
};

string classifyGeneration(EventTicket* ticket) {
    if (dynamic_cast<PremiumWorkshopTicket*>(ticket)) {
        return "Multilevel descendant (3 generations deep)";
    }
    else if (dynamic_cast<WorkshopTicket*>(ticket)) {
        return "Workshop descendant";
    }
    else if (dynamic_cast<HackathonTicket*>(ticket)) {
        return "Hierarchical sibling (independent branch)";
    }

    return "Standard Event Ticket";
}

double getTotalBalanceDue(vector<EventTicket*> tickets) {
    double total = 0;

    for (EventTicket* ticket : tickets) {
        total += ticket->getBalanceDue();
    }

    return total;
}

int main() {
    EventTicket standard("STU1", 500);
    WorkshopTicket workshop("STU2", 1200, "AI/ML");
    PremiumWorkshopTicket premium("STU3", 2000, "Cloud Native", 300);
    HackathonTicket hackathon("STU4", 800, "Byte Force");

    standard.printTicket();
    workshop.printTicket();
    premium.printTicket();
    hackathon.printTicket();

    cout << classifyGeneration(&premium) << endl;
    cout << classifyGeneration(&hackathon) << endl;

    vector<EventTicket*> tickets = {
        &standard, &workshop, &premium, &hackathon
    };

    cout << getTotalBalanceDue(tickets) << endl;

    return 0;
}