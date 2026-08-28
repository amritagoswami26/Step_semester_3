#include <bits/stdc++.h>
using namespace std;

class ParkingSlot {
private:
    string slotNo;
    int capacity;
    int occupiedCount;

public:
    ParkingSlot(string s, int c, int occupied = 0) {
        slotNo = s;
        capacity = c;
        occupiedCount = occupied;
    }

    void allot(string vehicleNo) {
        if (occupiedCount < capacity) {
            occupiedCount++;

            cout << vehicleNo
                 << " allotted to slot "
                 << slotNo << endl;
        }
        else {
            cout << "Slot is full" << endl;
        }
    }

    bool isAvailable() {
        return occupiedCount < capacity;
    }

    string getSlotNo() {
        return slotNo;
    }

    /*
    Passing the array does not copy the actual ParkingSlot
    objects for modification purposes here. The array elements
    are accessed directly, so changes to an object remain visible
    outside the method.
    */

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
        string vehicleNo
    ) {
        ParkingSlot* availableSlot =
            findAvailableSlot(slots, size);

        if (availableSlot != nullptr) {
            availableSlot->allot(vehicleNo);
        }
        else {
            cout << "No slots available for "
                 << vehicleNo << endl;
        }
    }
};


int main() {

    // Array containing an available slot
    ParkingSlot slots1[2] = {
        ParkingSlot("A1", 4, 3),
        ParkingSlot("A2", 5, 5)
    };

    ParkingSlot::safeAllot(
        slots1,
        2,
        "TN09AB1234"
    );


    cout << endl;


    // Array where all slots are full
    ParkingSlot slots2[2] = {
        ParkingSlot("A1", 4, 4),
        ParkingSlot("A2", 5, 5)
    };

    ParkingSlot::safeAllot(
        slots2,
        2,
        "TN09AB1234"
    );

    return 0;
}