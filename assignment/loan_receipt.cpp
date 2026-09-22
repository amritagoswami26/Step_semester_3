#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <stdexcept>
using namespace std;


class LoanReceipt {
private:
    const string memberId;
    const vector<string> bookIds;

public:

    LoanReceipt(
        string memberId,
        vector<string> bookIds
    ) : memberId(memberId),
        bookIds(bookIds) {

        regex pattern("^BK-[0-9]{3}$");

        for (string id : bookIds) {

            if (!regex_match(id, pattern)) {

                throw invalid_argument(
                    "Invalid book ID"
                );
            }
        }
    }


    // Defensive copy
    vector<string> getBookIds() const {
        return bookIds;
    }


    // Returns a NEW object
    LoanReceipt withCorrectedBookId(
        int index,
        string newId
    ) const {

        regex pattern("^BK-[0-9]{3}$");

        if (!regex_match(newId, pattern)) {
            throw invalid_argument(
                "Invalid book ID"
            );
        }

        if (index < 0 ||
            index >= bookIds.size()) {

            throw out_of_range(
                "Invalid index"
            );
        }

        vector<string> newBookIds =
            bookIds;

        newBookIds[index] = newId;

        return LoanReceipt(
            memberId,
            newBookIds
        );
    }


    virtual ~LoanReceipt() {}
};


class ReferenceOnlyLoanReceipt
    : public LoanReceipt {

private:
    string roomNumber;

public:

    ReferenceOnlyLoanReceipt(
        string memberId,
        vector<string> bookIds,
        string roomNumber
    )
        : LoanReceipt(
              memberId,
              bookIds
          ),
          roomNumber(roomNumber) {
    }
};


class NightlyProcessor {
public:

    static string processNightlyCirculation(
        vector<LoanReceipt*> receipts
    ) {

        int processed = 0;
        int nullSkipped = 0;
        int referenceOnly = 0;
        int regular = 0;

        for (LoanReceipt* receipt : receipts) {

            if (receipt == nullptr) {
                nullSkipped++;
                continue;
            }

            processed++;

            if (dynamic_cast<
                    ReferenceOnlyLoanReceipt*
                >(receipt) != nullptr) {

                referenceOnly++;
            }
            else {
                regular++;
            }
        }

        return to_string(processed) +
               " processed | " +

               to_string(nullSkipped) +
               " null skipped | " +

               to_string(referenceOnly) +
               " reference-only | " +

               to_string(regular) +
               " regular";
    }
};


int main() {

    try {

        // Normal receipt
        LoanReceipt r(
            "LIB-8841",
            {"BK-100", "BK-101"}
        );


        // Defensive copy test
        vector<string> ids =
            r.getBookIds();

        ids[0] = "HACKED";

        cout << r.getBookIds()[0]
             << endl;


        // Reference-only receipt
        ReferenceOnlyLoanReceipt reference(
            "LIB-001",
            {"BK-200"},
            "Reading Room 3"
        );


        // Regular receipt
        LoanReceipt regular(
            "LIB-002",
            {"BK-201"}
        );


        // Batch with nullptr
        vector<LoanReceipt*> receipts = {
            &reference,
            nullptr,
            &regular
        };


        cout <<
            NightlyProcessor::processNightlyCirculation(
                receipts
            )
            << endl;
    }

    catch (exception &e) {
        cout << "construction rejected"
             << endl;
    }

    return 0;
}