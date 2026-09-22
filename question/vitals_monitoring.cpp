#include <iostream>
#include <vector>
using namespace std;

class PatientVitals {
private:
    vector<double> readings;

public:

    PatientVitals(vector<double> initialReadings) {

        for (double reading : initialReadings) {
            recordReading(reading);
        }
    }


    void recordReading(double reading) {

        if (reading > 0 && reading <= 45) {
            readings.push_back(reading);
        }
    }


    double getAverage() {

        if (readings.empty())
            return 0;

        double sum = 0;

        for (double reading : readings)
            sum += reading;

        return sum / readings.size();
    }


    vector<double> getAllReadings() {

        // Return a copy
        return readings;
    }
};


int main() {

    PatientVitals v({
        36.5,
        -2,
        37.1
    });

    vector<double> result = v.getAllReadings();

    for (double x : result)
        cout << x << " ";

    cout << endl;

    // Defensive copy test
    result[0] = 999;

    vector<double> original = v.getAllReadings();

    cout << original[0] << endl;

    return 0;
}