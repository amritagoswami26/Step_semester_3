#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <regex>
using namespace std;


class DischargeSummary {

protected:
    string patientId;
    vector<string> medicationCodes;

public:

    DischargeSummary(string patientId,
                     vector<string> medicationCodes) {

        regex pattern("^MED-[A-Z]$");

        for (string code : medicationCodes) {

            if (!regex_match(code, pattern)) {
                throw invalid_argument(
                    "Invalid medication code"
                );
            }
        }

        this->patientId = patientId;
        this->medicationCodes = medicationCodes;
    }


    vector<string> getMedicationCodes() const {

        // Defensive copy
        return medicationCodes;
    }


    virtual DischargeSummary* withCorrectedMedication(
        int index,
        string newCode
    ) const {

        regex pattern("^MED-[A-Z]$");

        if (!regex_match(newCode, pattern))
            throw invalid_argument(
                "Invalid medication code"
            );

        vector<string> newCodes = medicationCodes;

        if (index < 0 ||
            index >= newCodes.size()) {

            throw out_of_range("Invalid index");
        }

        newCodes[index] = newCode;

        return new DischargeSummary(
            patientId,
            newCodes
        );
    }


    virtual ~DischargeSummary() {}
};


class CriticalCareDischargeSummary
    : public DischargeSummary {

private:
    int icuDays;

public:

    CriticalCareDischargeSummary(
        string patientId,
        vector<string> medicationCodes,
        int icuDays
    )
        : DischargeSummary(
              patientId,
              medicationCodes
          ) {

        this->icuDays = icuDays;
    }
};


class NightlyProcessor {

public:

    static string processNightlyBatch(
        vector<DischargeSummary*> summaries
    ) {

        int processed = 0;
        int nullSkipped = 0;
        int criticalCare = 0;
        int routine = 0;

        for (DischargeSummary* summary : summaries) {

            if (summary == nullptr) {
                nullSkipped++;
                continue;
            }

            processed++;

            if (dynamic_cast<CriticalCareDischargeSummary*>(
                    summary) != nullptr) {

                criticalCare++;
            }
            else {
                routine++;
            }
        }

        return to_string(processed) +
               " processed | " +
               to_string(nullSkipped) +
               " null skipped | " +
               to_string(criticalCare) +
               " critical-care | " +
               to_string(routine) +
               " routine";
    }
};


int main() {

    try {

        vector<string> codes = {
            "MED-A",
            "MED-B"
        };

        DischargeSummary d(
            "MT2026-0142",
            codes
        );

        vector<string> copy =
            d.getMedicationCodes();

        copy[0] = "TAMPERED";

        cout << d.getMedicationCodes()[0]
             << endl;


        CriticalCareDischargeSummary c(
            "MT001",
            {"MED-X"},
            4
        );

        DischargeSummary r(
            "MT002",
            {"MED-Y"}
        );


        vector<DischargeSummary*> batch = {
            &c,
            nullptr,
            &r
        };

        cout << NightlyProcessor::processNightlyBatch(
            batch
        ) << endl;
    }
    catch (exception &e) {
        cout << "construction rejected" << endl;
    }

    return 0;
}