#include <iostream>
#include <string>
using namespace std;

class Auditable {
public:
    virtual string auditRecord() = 0;
    virtual ~Auditable() {}
};

class StaffMember {
private:
    double baseSalary;

protected:
    double bonusRate;

public:
    StaffMember(double baseSalary) : StaffMember(baseSalary, 0.10) {}

    StaffMember(double baseSalary, double bonusRate) {
        this->baseSalary = baseSalary;
        this->bonusRate = bonusRate;
    }

    virtual double calculateBonus() = 0;

    double getSalary() {
        return baseSalary;
    }

    void setSalary(double baseSalary) {
        if (baseSalary >= 0) {
            this->baseSalary = baseSalary;
        }
    }

    virtual ~StaffMember() {}
};

class TeamLead : public StaffMember, public Auditable {
private:
    int teamSize;

public:
    TeamLead(double baseSalary, int teamSize)
        : StaffMember(baseSalary), teamSize(teamSize) {}

    TeamLead(double baseSalary, double bonusRate, int teamSize)
        : StaffMember(baseSalary, bonusRate), teamSize(teamSize) {}

    double calculateBonus() override {
        return getSalary() * bonusRate;
    }

    string auditRecord() override {
        return "TeamLead audit: " + to_string(teamSize) +
               " team members, salary $" + to_string(getSalary());
    }
};

string getAuditIfApplicable(StaffMember* s) {
    Auditable* a = dynamic_cast<Auditable*>(s);

    if (a != nullptr) {
        return a->auditRecord();
    }

    return "No audit required";
}

int main() {
    TeamLead t(60000, 5);

    cout << t.calculateBonus() << endl;

    TeamLead t2(60000, 0.20, 5);

    cout << t2.calculateBonus() << endl;

    t.setSalary(-5000);

    cout << t.getSalary() << endl;

    StaffMember* ref = &t;

    cout << getAuditIfApplicable(ref) << endl;

    return 0;
}