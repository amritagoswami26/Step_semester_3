#include <iostream>
#include <string>
#include <vector>
using namespace std;

class RaceEntry {
protected:
    string bibNumber;
    double entryFee;
    double amountPaid;

public:
    RaceEntry(string bibNumber, double entryFee) {
        this->bibNumber = bibNumber;
        this->entryFee = entryFee;
        amountPaid = 0;
    }

    virtual double getBalanceDue() {
        return entryFee - amountPaid;
    }

    virtual string announce() {
        return "Race Entry";
    }

    virtual ~RaceEntry() {}
};

class RunnerEntry : public RaceEntry {
private:
    string category;

public:
    RunnerEntry(string bibNumber, double entryFee, string category)
        : RaceEntry(bibNumber, entryFee) {
        this->category = category;
    }

    string announce() override {
        return "Runner Entry | Bib: " + bibNumber +
               " | Category: " + category +
               " | Balance: " + to_string(getBalanceDue());
    }
};

class RelayTeamEntry : public RaceEntry {
private:
    int teamSize;

public:
    RelayTeamEntry(string bibNumber, double entryFee, int teamSize)
        : RaceEntry(bibNumber, entryFee) {
        this->teamSize = teamSize;
    }

    int getTeamSize() {
        return teamSize;
    }

    string announce() override {
        return "Relay Team | Bib: " + bibNumber +
               " | Team Size: " + to_string(teamSize) +
               " | Balance: " + to_string(getBalanceDue());
    }
};

string announceAll(vector<RaceEntry*> entries) {
    string report = "";

    for (RaceEntry* entry : entries) {

        // Polymorphism
        report += entry->announce();

        // Safe downcasting
        RelayTeamEntry* relay =
            dynamic_cast<RelayTeamEntry*>(entry);

        if (relay != nullptr) {
            report += " [Team size via downcast: "
                   + to_string(relay->getTeamSize())
                   + "]";
        }

        report += " | ";
    }

    return report;
}

int main() {
    RunnerEntry runner("BIB2001", 80, "Open 10K");
    RelayTeamEntry relay("BIB4001", 300, 4);

    vector<RaceEntry*> fleet = {
        &runner,
        &relay
    };

    cout << announceAll(fleet) << endl;

    return 0;
}