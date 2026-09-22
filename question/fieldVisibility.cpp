#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

class AccessRuleEngine {
public:

    static string classifyAccess(string fieldModifier, string accessorContext) {

        if (fieldModifier == "private") {
            return accessorContext == "SAME_CLASS" ? "ALLOWED" : "DENIED";
        }

        if (fieldModifier == "default") {
            return (accessorContext == "SAME_CLASS" ||
                    accessorContext == "SAME_PACKAGE")
                   ? "ALLOWED" : "DENIED";
        }

        if (fieldModifier == "protected") {
            return (accessorContext == "SAME_CLASS" ||
                    accessorContext == "SAME_PACKAGE")
                   ? "ALLOWED" : "DENIED";
        }

        if (fieldModifier == "public") {
            return "ALLOWED";
        }

        return "DENIED";
    }

    static string summarizeBatch(vector<vector<string>> attempts) {

        int allowed = 0;
        int denied = 0;

        for (auto &attempt : attempts) {
            string result = classifyAccess(attempt[0], attempt[1]);

            if (result == "ALLOWED")
                allowed++;
            else
                denied++;
        }

        return "Allowed: " + to_string(allowed) +
               " | Denied: " + to_string(denied);
    }
};


class PatientRecord {
private:
    string patientId;

protected:
    string wardCode;

public:
    double vitalsScore;
    string facilityName;

    PatientRecord(string patientId,
                  string wardCode,
                  double vitalsScore,
                  string facilityName) {

        string trimmed = patientId;

        // Remove leading spaces
        trimmed.erase(trimmed.begin(),
                      find_if(trimmed.begin(), trimmed.end(),
                              [](unsigned char ch) {
                                  return !isspace(ch);
                              }));

        // Remove trailing spaces
        trimmed.erase(
            find_if(trimmed.rbegin(), trimmed.rend(),
                    [](unsigned char ch) {
                        return !isspace(ch);
                    }).base(),
            trimmed.end()
        );

        if (trimmed.empty() || trimmed.length() < 4) {
            throw invalid_argument("Invalid patient ID");
        }

        this->patientId = trimmed;
        this->wardCode = wardCode;
        this->vitalsScore = vitalsScore;
        this->facilityName = facilityName;
    }
};


int main() {

    cout << AccessRuleEngine::classifyAccess(
        "private", "SAME_CLASS"
    ) << endl;

    cout << AccessRuleEngine::classifyAccess(
        "default", "DIFFERENT_PACKAGE"
    ) << endl;

    vector<vector<string>> attempts = {
        {"protected", "SAME_PACKAGE"},
        {"protected", "DIFFERENT_PACKAGE"},
        {"public", "DIFFERENT_PACKAGE"}
    };

    cout << AccessRuleEngine::summarizeBatch(attempts) << endl;

    try {
        PatientRecord p(
            "MT94",
            "W3",
            98.2,
            "MediTrack Central"
        );

        cout << "Patient record created successfully" << endl;
    }
    catch (invalid_argument &e) {
        cout << "construction rejected" << endl;
    }

    return 0;
}