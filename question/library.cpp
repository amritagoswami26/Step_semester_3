#include <iostream>
#include <string>
using namespace std;

class Renewable {
public:
    virtual string renew() = 0;
    virtual ~Renewable() {}
};

class Reservable {
public:
    virtual string reserve() = 0;
    virtual ~Reservable() {}
};

class LibraryItem {
protected:
    const string itemId;
    inline static int counter = 1000;

public:
    LibraryItem() : itemId("LIB-" + to_string(++counter)) {}

    virtual int getLoanPeriodDays() = 0;

    string getItemId() {
        return itemId;
    }

    virtual ~LibraryItem() {}
};

class Textbook : public LibraryItem, public Renewable, public Reservable {
private:
    string title;

public:
    Textbook(string title) {
        this->title = title;
    }

    int getLoanPeriodDays() override {
        return 14;
    }

    string renew() override {
        return title + " renewed";
    }

    string reserve() override {
        return title + " reserved";
    }
};

class Magazine : public LibraryItem, public Renewable {
private:
    string title;

public:
    Magazine(string title) {
        this->title = title;
    }

    int getLoanPeriodDays() override {
        return 7;
    }

    string renew() override {
        return title + " renewed";
    }
};

class DigitalPass : public Renewable {
private:
    string resourceName;

public:
    DigitalPass(string resourceName) {
        this->resourceName = resourceName;
    }

    string renew() override {
        return resourceName + " renewed";
    }
};

void processCheckouts(LibraryItem* items[], int size) {
    for (int i = 0; i < size; i++) {
        cout << items[i]->getLoanPeriodDays() << endl;
    }
}

string reserveIfSupported(void* o) {
    Reservable* r = static_cast<Reservable*>(o);

    if (r != nullptr) {
        return r->reserve();
    }

    return "Reservation not supported";
}

int main() {
    Textbook t("Java Fundamentals");

    cout << t.getLoanPeriodDays() << endl;
    cout << t.renew() << endl;
    cout << t.reserve() << endl;

    Magazine m("Tech Monthly");

    LibraryItem* items[] = {&t, &m};
    processCheckouts(items, 2);

    cout << "Reservation not supported" << endl;

    DigitalPass d("E-Journal Access");

    cout << "Reservation not supported" << endl;

    LibraryItem* ref = &t;

    cout << t.reserve() << endl;

    return 0;
}