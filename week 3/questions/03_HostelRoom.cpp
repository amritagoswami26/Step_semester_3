#include <bits/stdc++.h>
using namespace std;

class HostelRoom {
private:
    string roomNo;
    int beds;
    int occupied;

public:
    // Default constructor
    HostelRoom() {
        roomNo = "";
        beds = 0;
        occupied = 0;
    }

    // Parameterized constructor
    HostelRoom(string r, int b) {
        roomNo = r;
        beds = b;
        occupied = 0;
    }

    void allot(string studentName) {
        if (occupied < beds) {
            occupied++;

            cout << studentName
                 << " allotted to room "
                 << roomNo << endl;
        }
        else {
            cout << "Room " << roomNo
                 << " is full. Student added to waiting list."
                 << endl;
        }
    }

    int getOccupied() {
        return occupied;
    }
};

int main() {
    // First object
    HostelRoom room214("C-214", 2);

    // Reference to the same object
    HostelRoom &sameRoom = room214;

    sameRoom.allot("Ravi");

    cout << "room214 occupied: "
         << room214.getOccupied() << endl;

    // Separate object with same values
    HostelRoom separateRoom("C-214", 2);

    cout << boolalpha;

    cout << "sameRoom == room214: "
         << (&sameRoom == &room214) << endl;

    cout << "separateRoom == room214: "
         << (&separateRoom == &room214) << endl;

    // Fill the room
    room214.allot("Anitha");

    // Room is already full
    room214.allot("Karthik");

    return 0;
}