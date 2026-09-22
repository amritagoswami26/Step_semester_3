#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

class RelayTeamEntry;

class RaceEntry {
private:
    static int bibCounter;
    const int entryCode;

protected:
    string bibNumber;
    double entryFee;
    double amountPaid;

public:
    RaceEntry(string bibNumber, double entryFee)
        : entryCode(++bibCounter) {

        this->bibNumber = bibNumber;
        this->entryFee = entryFee;
        this->amountPaid = 0;
    }

    // Flat payment
    void pay(double amount) {
        amountPaid += amount;
    }

    // Overloaded payment
    void pay(double amount, string mode) {
        pay(amount);
        cout << "Paying via " << mode << endl;
    }

    double getBalanceDue() {
        return entryFee - amountPaid;
    }

    // Discount code validation
    static bool isValidDiscountCode(string code) {

        if (code.length() != 5)
            return false;

        if (code[0] != 'M')
            return false;

        if (!isdigit(code[1]))
            return false;

        if (!isdigit(code[2]))
            return false;

        if (!isdigit(code[3]))
            return false;

        if (!isupper(code[4]))
            return false;

        return true;
    }

    static int getBibCounter() {
        return bibCounter;
    }

    // Declaration of static function
    static string settleNight(vector<RaceEntry*> entries);

    virtual ~RaceEntry() {}
};

int RaceEntry::bibCounter = 0;


// Relay Team
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
};


// Definition of static settleNight()
string RaceEntry::settleNight(vector<RaceEntry*> entries) {

    int processed = 0;
    int nullSkipped = 0;
    int relay = 0;
    int individual = 0;

    for (RaceEntry* entry : entries) {

        if (entry == nullptr) {
            nullSkipped++;
            continue;
        }

        processed++;

        if (dynamic_cast<RelayTeamEntry*>(entry) != nullptr) {
            relay++;
        }
        else {
            individual++;
        }
    }

    return to_string(processed) +
           " processed | " +
           to_string(nullSkipped) +
           " null skipped | " +
           to_string(relay) +
           " relay | " +
           to_string(individual) +
           " individual";
}


int main() {

    RaceEntry r1("BIB1001", 100);

    RaceEntry r2("BIB1002", 200);

    RelayTeamEntry relay("BIB4001", 300, 4);


    // Discount code testing
    cout << boolalpha;

    cout << RaceEntry::isValidDiscountCode("M123A") << endl;

    cout << RaceEntry::isValidDiscountCode("M12A") << endl;

    cout << RaceEntry::isValidDiscountCode("X123A") << endl;


    // Payment
    r1.pay(10, "UPI");


    // Night settlement
    vector<RaceEntry*> entries = {
        &r1,
        nullptr,
        &relay
    };

    cout << RaceEntry::settleNight(entries) << endl;


    // Counter
    cout << RaceEntry::getBibCounter() << endl;


    return 0;
}