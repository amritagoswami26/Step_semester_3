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

    void pay(double amount) {
        amountPaid += amount;
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
protected:
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

class EliteRunnerEntry : public RunnerEntry {
private:
    double sponsorBonus;

public:
    EliteRunnerEntry(string bibNumber, double entryFee,
                     string category, double sponsorBonus)
        : RunnerEntry(bibNumber, entryFee, category) {
        this->sponsorBonus = sponsorBonus;
    }

    string announce() override {
        return "Elite Runner | Bib: " + bibNumber +
               " | Category: " + category +
               " | Sponsor Bonus: " + to_string(sponsorBonus) +
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

string classifyGeneration(RaceEntry* entry) {
    if (dynamic_cast<EliteRunnerEntry*>(entry)) {
        return "Multilevel descendant (3 generations deep)";
    }
    else if (dynamic_cast<RelayTeamEntry*>(entry)) {
        return "Hierarchical sibling (independent branch)";
    }
    else if (dynamic_cast<RunnerEntry*>(entry)) {
        return "Single inheritance";
    }

    return "Base class";
}

double getTotalBalanceDue(vector<RaceEntry*> entries) {
    double total = 0;

    for (RaceEntry* entry : entries) {
        total += entry->getBalanceDue();
    }

    return total;
}

int main() {
    RunnerEntry runner("BIB2001", 80, "Open 10K");

    EliteRunnerEntry elite(
        "BIB3001", 150,
        "Elite Full Marathon", 500
    );

    RelayTeamEntry relay("BIB4001", 300, 4);

    cout << runner.announce() << endl;
    cout << elite.announce() << endl;
    cout << relay.announce() << endl;

    cout << classifyGeneration(&elite) << endl;
    cout << classifyGeneration(&relay) << endl;

    vector<RaceEntry*> entries = {
        &runner, &elite, &relay
    };

    cout << getTotalBalanceDue(entries) << endl;

    return 0;
}