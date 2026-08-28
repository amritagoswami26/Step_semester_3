#include <bits/stdc++.h>
using namespace std;
class FeeAccount {
private:
    double totalFee;
    double amountPaid;

public:
    FeeAccount(double fee) {
        totalFee = fee;
        amountPaid = 0;
    }

    void pay(double amount) {
        if (amount > 0) {
            amountPaid += amount;

            if (amountPaid > totalFee) {
                amountPaid = totalFee;
            }
        }
    }

    void payInTwoInstallments(double amount) {
        pay(amount / 2);
        pay(amount / 2);
    }

    double getDue() {
        return totalFee - amountPaid;
    }
};

class HostelRoom {
private:
    string roomNo;
    int beds;
    int occupied;

public:
    HostelRoom(string r, int b) {
        roomNo = r;
        beds = b;
        occupied = 0;
    }

    void allot(string studentName) {
        if (occupied < beds) {
            occupied++;
        }
        else {
            cout << "Room is full. Waiting list." << endl;
        }
    }

    string getRoomNo() {
        return roomNo;
    }
};


class SrmStudent {
private:
    string name;
    string regNo;
    FeeAccount feeAccount;
    HostelRoom room;

public:
    static int totalStudents;

    // Constructor
    SrmStudent(string n, string r,
               double fee,
               string roomNo,
               int beds)
        : feeAccount(fee), room(roomNo, beds) {

        name = n;
        regNo = r;

        totalStudents++;
    }

    void processPayment(double amount) {
        feeAccount.pay(amount);
    }

    void processInstallment(double amount) {
        feeAccount.payInTwoInstallments(amount);
    }

    void allotRoom() {
        room.allot(name);
    }

    void fullStatus() {
        cout << name
             << " | Due: Rs "
             << feeAccount.getDue()
             << " | Room: "
             << room.getRoomNo()
             << endl;
    }
};


// Static member definition
int SrmStudent::totalStudents = 0;

int main() {

    SrmStudent s1(
        "Ravi",
        "RA231100301",
        200000,
        "C-214",
        2
    );

    SrmStudent s2(
        "Anitha",
        "RA231100302",
        180000,
        "C-507",
        2
    );

    SrmStudent s3(
        "Karthik",
        "RA231100303",
        150000,
        "C-309",
        2
    );


    // Process payments
    s1.processInstallment(120000);
    s2.processPayment(40000);


    // Allot rooms
    s1.allotRoom();
    s2.allotRoom();
    s3.allotRoom();


    // Display status
    s1.fullStatus();
    s2.fullStatus();
    s3.fullStatus();
    cout << "Total students: "
         << SrmStudent::totalStudents
         << endl;

    return 0;
}