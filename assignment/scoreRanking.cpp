#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

class Canteen {
private:
    string canteenCode;
    string canteenName;
    int trustScore;

public:

    Canteen(string canteenCode, string canteenName, int trustScore) {
        this->canteenCode = canteenCode;
        this->canteenName = canteenName;
        this->trustScore = trustScore;
    }

    // Default trust score = 3
    Canteen(string canteenCode, string canteenName)
        : Canteen(canteenCode, canteenName, 3) {
    }

    string getCode() const {
        return canteenCode;
    }

    int compareTo(const Canteen &other) const {

        // Higher trust score comes first
        if (trustScore > other.trustScore)
            return -1;

        if (trustScore < other.trustScore)
            return 1;

        // Convert codes to lowercase for comparison
        string code1 = canteenCode;
        string code2 = other.canteenCode;

        for (char &c : code1)
            c = tolower(c);

        for (char &c : code2)
            c = tolower(c);

        // Alphabetical order of code
        if (code1 < code2)
            return -1;

        if (code1 > code2)
            return 1;

        // If code is same, shorter name first
        if (canteenName.length() < other.canteenName.length())
            return -1;

        if (canteenName.length() > other.canteenName.length())
            return 1;

        return 0;
    }

    static vector<Canteen> rankCanteens(vector<Canteen> canteens) {

        int n = canteens.size();

        // Manual Bubble Sort
        for (int i = 0; i < n - 1; i++) {

            for (int j = 0; j < n - i - 1; j++) {

                if (canteens[j].compareTo(canteens[j + 1]) > 0) {

                    Canteen temp = canteens[j];
                    canteens[j] = canteens[j + 1];
                    canteens[j + 1] = temp;
                }
            }
        }

        return canteens;
    }
};

int main() {

    vector<Canteen> canteens = {
        Canteen("HB3-C", "Spice Junction", 3),
        Canteen("hb1-c", "Grand Mess", 5),
        Canteen("HB2-C", "Southern Treats")
    };

    vector<Canteen> result = Canteen::rankCanteens(canteens);

    for (auto &canteen : result) {
        cout << "\"" << canteen.getCode() << "\" ";
    }

    return 0;
}