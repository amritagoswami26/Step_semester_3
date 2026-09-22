#include <iostream>
#include <string>
using namespace std;

class PaymentMethod {
protected:
    const string transactionId;
    inline static int counter = 1000;

public:
    PaymentMethod() : transactionId("TXN-" + to_string(++counter)) {}

    virtual string processPayment(double amount) = 0;

    string processPayment(double amount, string note) {
        return processPayment(amount) + " (" + note + ")";
    }

    string getTransactionId() const {
        return transactionId;
    }

    virtual ~PaymentMethod() = default;
};

class CreditCardPayment : public PaymentMethod {
private:
    string cardNumber;

public:
    using PaymentMethod::processPayment;

    CreditCardPayment(string cardNumber) : cardNumber(cardNumber) {}

    string processPayment(double amount) override {
        return "Charged $" + to_string(amount) + " to card ending " +
               cardNumber + " - " + transactionId;
    }
};

class CashPayment : public PaymentMethod {
public:
    CashPayment() {}

    string processPayment(double amount) override {
        return "Received $" + to_string(amount) + " in cash - " + transactionId;
    }
};

void printConfirmation(PaymentMethod& payment, double amount) {
    cout << payment.processPayment(amount) << endl;
}

int main() {
    CreditCardPayment cc("4471");
    cout << cc.processPayment(250.0) << endl;

    CashPayment cash;
    cout << cash.processPayment(40.0) << endl;

    cout << cc.processPayment(250.0, "Birthday gift") << endl;

    PaymentMethod& ref = cc;
    printConfirmation(ref, 250.0);

    return 0;
}