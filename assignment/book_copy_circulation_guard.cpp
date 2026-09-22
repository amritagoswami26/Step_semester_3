#include <iostream>
#include <stdexcept>
using namespace std;

class BookInventory {
private:
    int copiesTotal;
    int copiesAvailable;

public:

    BookInventory(int copiesTotal) {

        if (copiesTotal <= 0) {
            throw invalid_argument(
                "Invalid copies total"
            );
        }

        this->copiesTotal = copiesTotal;
        this->copiesAvailable = copiesTotal;
    }


    void checkOut() {

        if (copiesAvailable > 0) {
            copiesAvailable--;
        }
    }


    void checkIn() {

        if (copiesAvailable < copiesTotal) {
            copiesAvailable++;
        }
    }


    int getCopiesAvailable() {
        return copiesAvailable;
    }
};


int main() {

    try {

        BookInventory b(3);

        b.checkOut();
        b.checkOut();
        b.checkOut();

        // Fourth checkout rejected
        b.checkOut();

        cout << b.getCopiesAvailable()
             << endl;


        b.checkIn();
        b.checkIn();
        b.checkIn();

        // Fourth check-in rejected
        b.checkIn();

        cout << b.getCopiesAvailable()
             << endl;
    }

    catch (exception &e) {
        cout << "construction rejected"
             << endl;
    }

    return 0;
}