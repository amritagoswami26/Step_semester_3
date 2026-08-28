#include <bits/stdc++.h>
using namespace std;

class SrmStudent {
private:
    string name;
    string regNo;

    static string university;
    static int admissionCount;

public:
    // Constructor
    SrmStudent(string n) {
        name = n;

        admissionCount++;

        regNo = "RA231100" + to_string(300 + admissionCount);
    }

    // Instance method
    void printCard() {
        cout << name << " | "
             << regNo << " | "
             << university << endl;
    }

    // Static method
    static void printTotalAdmissions() {
        cout << "Total admissions so far: "
             << admissionCount << endl;
    }
};

// Definition of static members
string SrmStudent::university =
    "SRM Institute of Science and Technology";

int SrmStudent::admissionCount = 0;

int main() {
    SrmStudent s1("Ravi");
    SrmStudent s2("Meera");
    SrmStudent s3("Karthik");

    s1.printCard();
    s2.printCard();
    s3.printCard();

    SrmStudent::printTotalAdmissions();

    return 0;
}