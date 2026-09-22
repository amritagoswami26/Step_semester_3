#include <iostream>
#include <string>
using namespace std;

class DeliverySlot {
private:
    string orderId;
    string timeSlot;

public:

    // Main constructor
    DeliverySlot(string orderId, string timeSlot) {
        this->orderId = orderId;
        this->timeSlot = timeSlot;
    }

    // Constructor chaining
    DeliverySlot(string orderId)
        : DeliverySlot(orderId, "ASAP") {
    }

    bool isPeakHour() {

        return timeSlot == "12:00-13:00" ||
               timeSlot == "13:00-14:00" ||
               timeSlot == "19:00-20:00" ||
               timeSlot == "20:00-21:00";
    }
};

int main() {

    DeliverySlot slot1("ORD101", "13:00-14:00");
    DeliverySlot slot2("ORD102");

    cout << boolalpha;

    cout << slot1.isPeakHour() << endl;
    cout << slot2.isPeakHour() << endl;

    return 0;
}