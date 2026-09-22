#include <iostream>
#include <string>
#include <functional>
#include <cctype>
using namespace std;

class LibraryMember {
private:
    string membershipId;
    string name;
    bool premiumMember;

    // Stored but never exposed
    string securityAnswerHash;


public:

    // No-argument constructor
    LibraryMember()
        : LibraryMember("", "") {
    }


    // Name-only constructor
    LibraryMember(string name)
        : LibraryMember("", name) {
    }


    // Main constructor
    LibraryMember(string membershipId,
                  string name) {

        this->membershipId = membershipId;
        this->name = name;
        this->premiumMember = false;
    }


    string getMembershipId() {
        return membershipId;
    }


    void setMembershipId(string id) {

        // Write once
        if (membershipId.empty()) {
            membershipId = id;
        }
    }


    bool isPremiumMember() {
        return premiumMember;
    }


    void setPremiumMember(bool premium) {
        premiumMember = premium;
    }


    // Write-only property
    void setSecurityAnswer(string answer) {

        // Deterministic one-way transformation
        securityAnswerHash =
            to_string(
                hash<string>{}(answer)
            );
    }
};


int main() {

    LibraryMember m1("Priya Nair");

    cout << m1.getMembershipId()
         << endl;


    LibraryMember m2(
        "LIB-8841",
        "Priya Nair"
    );

    cout << m2.getMembershipId()
         << endl;


    LibraryMember m3;

    m3.setMembershipId("LIB-8841");

    // Ignored
    m3.setMembershipId("FAKE-0000");

    cout << m3.getMembershipId()
         << endl;


    m3.setSecurityAnswer("Blue");

    return 0;
}