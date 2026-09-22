#include <iostream>
#include <string>
#include <functional>
using namespace std;

class PatientProfile {
private:
    string patientId;
    string name;
    bool discharged;
    string lockerPinHash;

public:

    // No-argument constructor
    PatientProfile()
        : PatientProfile("", "") {
    }


    // Name-only constructor
    PatientProfile(string name)
        : PatientProfile("", name) {
    }


    // Main constructor
    PatientProfile(string patientId, string name) {

        this->patientId = patientId;
        this->name = name;
        this->discharged = false;
    }


    string getPatientId() {
        return patientId;
    }


    void setPatientId(string id) {

        // Write once
        if (patientId.empty()) {
            patientId = id;
        }
    }


    bool isDischarged() {
        return discharged;
    }


    void setDischarged(bool discharged) {
        this->discharged = discharged;
    }


    // Write-only PIN
    void setLockerPin(string pin) {

        if (pin.length() >= 4 &&
            pin.length() <= 6) {

            bool valid = true;

            for (char c : pin) {
                if (!isdigit(c)) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                lockerPinHash =
                    to_string(hash<string>{}(pin));
            }
        }
    }
};


int main() {

    PatientProfile p1("Arjun Iyer");

    cout << p1.getPatientId() << endl;

    PatientProfile p2(
        "MT2026-0142",
        "Arjun Iyer"
    );

    cout << p2.getPatientId() << endl;


    PatientProfile p3;

    p3.setPatientId("MT2026-0142");
    p3.setPatientId("HACKED-0000");

    cout << p3.getPatientId() << endl;


    p3.setLockerPin("1234");

    return 0;
}