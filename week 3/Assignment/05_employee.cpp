#include <bits/stdc++.h>
using namespace std;

class Employee {
private:
    string empId;
    string empName;
    double salary;

public:
    Employee(string id, string name, double sal) {
        empId = id;
        empName = name;
        salary = sal;
    }

    virtual ~Employee() {}

    double getSalary() {
        return salary;
    }

    string getName() {
        return empName;
    }

    string getEmpId() {
        return empId;
    }
};

class ManagerEmployee : public Employee {
private:
    double teamBonus;

public:
    ManagerEmployee(
        string id,
        string name,
        double sal,
        double bonus
    ) : Employee(id, name, sal) {

        teamBonus = bonus;
    }

    double effectiveSalary() {
        return getSalary() + teamBonus;
    }
};

class ParkingSlot {
private:
    string slotNo;
    int capacity;
    int occupiedCount;

public:
    ParkingSlot(
        string s,
        int c,
        int occupied = 0
    ) {
        slotNo = s;
        capacity = c;
        occupiedCount = occupied;
    }

    bool isAvailable() {
        return occupiedCount < capacity;
    }

    void allot(string vehicleNo) {
        if (isAvailable()) {
            occupiedCount++;
        }
    }

    string getSlotNo() {
        return slotNo;
    }

    static ParkingSlot* findAvailableSlot(
        ParkingSlot slots[],
        int size
    ) {
        for (int i = 0; i < size; i++) {

            if (slots[i].isAvailable()) {
                return &slots[i];
            }
        }

        return nullptr;
    }

    static void safeAllot(
        ParkingSlot slots[],
        int size,
        string vehicleNo,
        ParkingSlot*& assignedSlot
    ) {
        ParkingSlot* available =
            findAvailableSlot(slots, size);

        if (available != nullptr) {
            available->allot(vehicleNo);
            assignedSlot = available;
        }
        else {
            assignedSlot = nullptr;
        }
    }
};

class CompanyEmployeeRecord {
private:
    string name;
    string empId;

    // Object field
    Employee* employee;

    // Object reference
    ParkingSlot* slot;

public:
    static int totalRecords;

    CompanyEmployeeRecord(
        string n,
        string id,
        Employee* e
    ) {
        name = n;
        empId = id;
        employee = e;
        slot = nullptr;

        totalRecords++;
    }


    void assignParking(ParkingSlot* s) {
        slot = s;
    }


    void fullProfile() {

        double pay;

        // Check whether employee is a ManagerEmployee
        ManagerEmployee* manager =
            dynamic_cast<ManagerEmployee*>(employee);

        if (manager != nullptr) {
            pay = manager->effectiveSalary();
        }
        else {
            pay = employee->getSalary();
        }

        cout << name
             << " | Pay: Rs "
             << fixed
             << setprecision(1)
             << pay
             << " | Slot: ";

        // Null-safe check
        if (slot != nullptr) {
            cout << slot->getSlotNo();
        }
        else {
            cout << "no parking assigned";
        }

        cout << endl;
    }
};


// Static counter definition
int CompanyEmployeeRecord::totalRecords = 0;

int main() {

    // Create employees

    ManagerEmployee manager(
        "E101",
        "Divya",
        70000,
        8000
    );

    Employee employee(
        "E102",
        "Karan",
        49000
    );

    Employee employee2(
        "E103",
        "Meera",
        10000
    );


    // Create employee records

    CompanyEmployeeRecord r1(
        "Divya",
        "E101",
        &manager
    );

    CompanyEmployeeRecord r2(
        "Karan",
        "E102",
        &employee
    );

    CompanyEmployeeRecord r3(
        "Meera",
        "E103",
        &employee2
    );


    // Create parking slots

    ParkingSlot slots[2] = {
        ParkingSlot("A1", 1),
        ParkingSlot("A2", 1)
    };


    // Allot parking to first employee

    ParkingSlot* assigned1 = nullptr;

    ParkingSlot::safeAllot(
        slots,
        2,
        "TN01AB1111",
        assigned1
    );

    r1.assignParking(assigned1);


    // Allot parking to second employee

    ParkingSlot* assigned2 = nullptr;

    ParkingSlot::safeAllot(
        slots,
        2,
        "TN01AB2222",
        assigned2
    );

    r2.assignParking(assigned2);

    // Print profiles

    r1.fullProfile();
    r2.fullProfile();
    r3.fullProfile();


    cout << "Total records: "
         << CompanyEmployeeRecord::totalRecords
         << endl;

    return 0;
}