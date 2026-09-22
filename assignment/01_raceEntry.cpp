#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

class RaceEntry {
protected:
    string bibNumber;
    double entryFee;
    double amountPaid;

public:
    RaceEntry(string bibNumber, double entryFee) {
        if (bibNumber.empty() || bibNumber.find_first_not_of(' ') == string::npos ||
            bibNumber.length() < 4) {
            throw invalid_argument("Invalid bib number");
        }

        this->bibNumber = bibNumber;
        this->entryFee = entryFee;
        this->amountPaid = 0;
    }

    virtual ~RaceEntry() {}

    void pay(double amount) {
        amountPaid += amount;
    }

    virtual double getBalanceDue() {
        return entryFee - amountPaid;
    }

    virtual string announce() {
        return "Race Entry | Bib: " + bibNumber +
               " | Balance: " + to_string(getBalanceDue());
    }

    static string registerBatch(vector<string> bibNumbers, double entryFee) {
        int registered = 0;
        int rejected = 0;

        for (string bib : bibNumbers) {
            try {
                RaceEntry r(bib, entryFee);
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

class RunnerEntry : public RaceEntry {
private:
    string category;

public:
    RunnerEntry(string bibNumber, double entryFee, string category)
        : RaceEntry(bibNumber, entryFee), category(category) {}

    string announce() override {
        return "Runner Entry | Bib: " + bibNumber +
               " | Category: " + category +
               " | Balance: " + to_string(getBalanceDue());
    }
};

int main() {
    RunnerEntry r("BIB2001", 80, "Open 10K");

    r.pay(30);

    cout << r.getBalanceDue() << endl;

    vector<string> bibs = {"BIB1", "B1", "BIB2"};

    cout << RaceEntry::registerBatch(bibs, 80) << endl;

    return 0;
}