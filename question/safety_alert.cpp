#include <iostream>
#include <string>
using namespace std;

class Alertable {
public:
    virtual string sendAlert(string message) = 0;
    virtual ~Alertable() {}
};

class SecuritySensor {
protected:
    string zoneName;

public:
    SecuritySensor(string zoneName) {
        this->zoneName = zoneName;
    }

    string getZoneName() {
        return zoneName;
    }

    virtual ~SecuritySensor() {}
};

class MotionSensor : public SecuritySensor, public Alertable {
public:
    MotionSensor(string zoneName) : SecuritySensor(zoneName) {}

    string sendAlert(string message) override {
        return "[" + zoneName + "] " + message;
    }
};

class DualZoneMotionSensor : public MotionSensor {
private:
    string secondZoneName;

public:
    DualZoneMotionSensor(string zoneName, string secondZoneName)
        : MotionSensor(zoneName) {
        this->secondZoneName = secondZoneName;
    }

    string sendAlert(string message) override {
        return MotionSensor::sendAlert(message) +
               " [also covering " + secondZoneName + "]";
    }
};

class SmokeDetector : public Alertable {
private:
    string deviceId;

public:
    SmokeDetector(string deviceId) {
        this->deviceId = deviceId;
    }

    string sendAlert(string message) override {
        return "[" + deviceId + "] " + message;
    }
};

void broadcastAll(Alertable* devices[], int size, string message) {
    for (int i = 0; i < size; i++) {
        cout << devices[i]->sendAlert(message) << endl;
    }
}

string getZoneIfMotionSensor(Alertable* a) {
    MotionSensor* m = dynamic_cast<MotionSensor*>(a);

    if (m != nullptr) {
        return m->getZoneName();
    }

    return "Not a motion sensor";
}

int main() {
    MotionSensor m("Living Room");

    cout << m.sendAlert("Motion detected") << endl;

    DualZoneMotionSensor d("Hallway", "Stairwell");

    cout << d.sendAlert("Motion detected") << endl;

    SmokeDetector s("SD-01");

    cout << s.sendAlert("Smoke detected") << endl;

    Alertable* devices[] = {&m, &d, &s};

    broadcastAll(devices, 3, "Alert detected");

    cout << getZoneIfMotionSensor(&m) << endl;
    cout << getZoneIfMotionSensor(&s) << endl;

    return 0;
}