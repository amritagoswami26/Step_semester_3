#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cctype>
using namespace std;

class FoodOrder {
private:
    string studentName;
    string dishName;
    bool delivered;

    bool isBlank(string str) {
        if (str.empty())
            return true;

        for (char c : str) {
            if (!isspace(c))
                return false;
        }

        return true;
    }

public:
    // Parameterized constructor only
    FoodOrder(string studentName, string dishName) {

        if (isBlank(studentName) || isBlank(dishName)) {
            throw invalid_argument("Invalid order");
        }

        this->studentName = studentName;
        this->dishName = dishName;
        this->delivered = false;
    }

    void markDelivered() {

        if (!delivered) {
            delivered = true;
            cout << "Order marked as delivered." << endl;
        }
        else {
            cout << "Order was already delivered." << endl;
        }
    }
};

class OrderProcessor {
public:
    static void processBatch(vector<vector<string>> rawOrders) {

        int valid = 0;
        int rejected = 0;

        for (auto &order : rawOrders) {

            try {
                FoodOrder obj(order[0], order[1]);
                valid++;
            }
            catch (exception &e) {
                rejected++;
            }
        }

        cout << "Valid: " << valid
             << " | Rejected: " << rejected << endl;
    }
};

int main() {

    vector<vector<string>> orders = {
        {"Ravi", "Paneer Butter Masala"},
        {"", "Chole Bhature"},
        {"Meera", " "},
        {"Divya", "Veg Biryani"}
    };

    OrderProcessor::processBatch(orders);

    return 0;
}