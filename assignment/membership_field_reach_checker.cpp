#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <stdexcept>
using namespace std;

class AccessChecker {
public:
    static string classifyAccess(string fieldModifier, string accessorContext) {

        if (fieldModifier == "private") {
            return accessorContext == "SAME_CLASS"
                   ? "ALLOWED" : "DENIED";
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

    static string summarizeByModifier(
        vector<vector<string>> attempts) {

        int privateAllowed = 0, privateDenied = 0;
        int defaultAllowed = 0, defaultDenied = 0;
        int protectedAllowed = 0, protectedDenied = 0;
        int publicAllowed = 0, publicDenied = 0;

        for (auto &attempt : attempts) {

            string modifier = attempt[0];
            string context = attempt[1];

            string result =
                classifyAccess(modifier, context);

            if (modifier == "private") {
                if (result == "ALLOWED")
                    privateAllowed++;
                else
                    privateDenied++;
            }

            else if (modifier == "default") {
                if (result == "ALLOWED")
                    defaultAllowed++;
                else
                    defaultDenied++;
            }

            else if (modifier == "protected") {
                if (result == "ALLOWED")
                    protectedAllowed++;
                else
                    protectedDenied++;
            }

            else if (modifier == "public") {
                if (result == "ALLOWED")
                    publicAllowed++;
                else
                    publicDenied++;
            }
        }

        return "private: " +
               to_string(privateAllowed) + " allowed / " +
               to_string(privateDenied) + " denied | " +

               "default: " +
               to_string(defaultAllowed) + " allowed / " +
               to_string(defaultDenied) + " denied | " +

               "protected: " +
               to_string(protectedAllowed) + " allowed / " +
               to_string(protectedDenied) + " denied | " +

               "public: " +
               to_string(publicAllowed) + " allowed / " +
               to_string(publicDenied) + " denied";
    }
};


class LibraryMember {
private:
    string membershipId;

protected:
    string branchCode;

public:
    double finesOwed;
    string displayName;

    LibraryMember(string membershipId,
                  string branchCode,
                  double finesOwed,
                  string displayName) {

        // Trim leading spaces
        membershipId.erase(
            membershipId.begin(),
            find_if(
                membershipId.begin(),
                membershipId.end(),
                [](unsigned char c) {
                    return !isspace(c);
                }
            )
        );

        // Trim trailing spaces
        membershipId.erase(
            find_if(
                membershipId.rbegin(),
                membershipId.rend(),
                [](unsigned char c) {
                    return !isspace(c);
                }
            ).base(),
            membershipId.end()
        );

        if (membershipId.empty() ||
            membershipId.length() < 4) {

            throw invalid_argument(
                "Invalid membership ID"
            );
        }

        this->membershipId = membershipId;
        this->branchCode = branchCode;
        this->finesOwed = finesOwed;
        this->displayName = displayName;
    }
};


int main() {

    cout << AccessChecker::classifyAccess(
        "private",
        "SAME_CLASS"
    ) << endl;

    cout << AccessChecker::classifyAccess(
        "protected",
        "DIFFERENT_PACKAGE"
    ) << endl;


    vector<vector<string>> attempts = {
        {"private", "SAME_CLASS"},
        {"private", "SAME_PACKAGE"},
        {"default", "SAME_PACKAGE"},
        {"default", "DIFFERENT_PACKAGE"},
        {"protected", "SAME_PACKAGE"},
        {"protected", "SAME_CLASS"},
        {"public", "DIFFERENT_PACKAGE"}
    };

    cout << AccessChecker::summarizeByModifier(
        attempts
    ) << endl;


    try {
        LibraryMember m(
            "LB9",
            "BR1",
            0,
            "Priya Nair"
        );
    }
    catch (exception &e) {
        cout << "construction rejected" << endl;
    }

    return 0;
}