#include <bits/stdc++.h>
using namespace std;

class SrmStudent {
private:
    string name;
    string regNo;
    int attendance;

public:
    // Constructor
    SrmStudent(string n, string r, int a) {
        name = n;
        regNo = r;
        attendance = a;
    }

    // Instance method
    void addAttendanceUpdate(int newAttendance) {
        attendance = newAttendance;
    }

    // Instance method
    bool isEligible() {
        return attendance >= 75;
    }

    // Static method
    static double classAverage(SrmStudent students[], int size) {
        int sum = 0;

        for (int i = 0; i < size; i++) {
            sum += students[i].attendance;
        }

        return (double)sum / size;
    }

    void display() {
        cout << name << " - " << attendance << "% - ";

        if (isEligible())
            cout << "Eligible";
        else
            cout << "Detained";

        cout << endl;
    }
};

int main() {
    SrmStudent students[5] = {
        SrmStudent("Ravi", "RA231100301", 82),
        SrmStudent("Anitha", "RA231100302", 68),
        SrmStudent("Karthik", "RA231100303", 91),
        SrmStudent("Meera", "RA231100304", 74),
        SrmStudent("Suresh", "RA231100305", 60)
    };

    for (int i = 0; i < 5; i++) {
        students[i].display();
    }

    cout << fixed << setprecision(1);
    cout << "Class average: "
         << SrmStudent::classAverage(students, 5)
         << "%" << endl;

    return 0;
}