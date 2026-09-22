#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

class BusRoute {
private:
    string routeCode;
    string routeName;
    int priority;

public:

    // Main constructor
    BusRoute(string routeCode,
             string routeName,
             int priority) {

        this->routeCode = routeCode;
        this->routeName = routeName;
        this->priority = priority;
    }


    // Constructor chaining
    BusRoute(string routeCode,
             string routeName)
        : BusRoute(routeCode, routeName, 5) {
    }


    string getRouteCode() const {
        return routeCode;
    }


    int compareTo(const BusRoute &other) const {

        // First priority
        if (priority < other.priority)
            return -1;

        if (priority > other.priority)
            return 1;


        // Compare route codes ignoring case
        string a = routeCode;
        string b = other.routeCode;

        for (char &c : a)
            c = tolower(c);

        for (char &c : b)
            c = tolower(c);


        if (a < b)
            return -1;

        if (a > b)
            return 1;


        // Completely equal
        return 0;
    }


    static vector<BusRoute> rankRoutes(
        vector<BusRoute> routes) {

        int n = routes.size();

        // Bubble sort
        for (int i = 0; i < n - 1; i++) {

            for (int j = 0; j < n - i - 1; j++) {

                if (routes[j].compareTo(
                        routes[j + 1]) > 0) {

                    BusRoute temp = routes[j];

                    routes[j] = routes[j + 1];

                    routes[j + 1] = temp;
                }
            }
        }

        return routes;
    }
};


int main() {

    vector<BusRoute> routes = {

        BusRoute(
            "RT205L",
            "Airport Express",
            3
        ),

        BusRoute(
            "rt201j",
            "City Central",
            4
        ),

        BusRoute(
            "RT299T",
            "Night Service"
        )
    };


    vector<BusRoute> ranked =
        BusRoute::rankRoutes(routes);


    for (BusRoute &route : ranked) {
        cout << "\"" << route.getRouteCode()
             << "\"" << endl;
    }

    return 0;
}