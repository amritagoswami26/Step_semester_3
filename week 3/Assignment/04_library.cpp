#include <bits/stdc++.h>
using namespace std;

class BrokenLibraryMember {
public:
    static string name;
    static string memberId;
    static int booksIssued;

    BrokenLibraryMember(
        string n,
        string id,
        int books
    ) {
        name = n;
        memberId = id;
        booksIssued = books;
    }

    void printMember() {
        cout << name
             << " | "
             << memberId
             << endl;
    }
};


// Static member definitions
string BrokenLibraryMember::name = "";
string BrokenLibraryMember::memberId = "";
int BrokenLibraryMember::booksIssued = 0;

class LibraryMember {
private:
    // Different for every object
    string name;
    string memberId;
    int booksIssued;

    // Shared by all objects
    static string libraryName;
    static int memberCount;

public:

    LibraryMember(string n, int books) {
        name = n;
        booksIssued = books;

        memberCount++;

        memberId =
            "LM-" + to_string(1000 + memberCount);
    }

    void printMemberCard() {
        cout << name
             << " | "
             << memberId
             << endl;
    }

    static void printTotalMembers() {
        cout << "Total members: "
             << memberCount
             << endl;
    }
};


// Static member definitions
string LibraryMember::libraryName =
    "Central Library";

int LibraryMember::memberCount = 0;

int main() {

    cout << "BROKEN VERSION" << endl;

    
    BrokenLibraryMember b1(
        "Aditi",
        "LM-1001",
        2
    );

    BrokenLibraryMember b2(
        "Rohan",
        "LM-1002",
        3
    );

    // Both objects now show Rohan's data
    b1.printMember();
    b2.printMember();


    cout << endl;
    cout << "FIXED VERSION" << endl;

    LibraryMember m1("Aditi", 2);
    LibraryMember m2("Rohan", 3);

    m1.printMemberCard();
    m2.printMemberCard();

    LibraryMember::printTotalMembers();

    return 0;
}