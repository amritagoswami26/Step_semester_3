#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
using namespace std;

class AccessRuleEngine {
public:

    static string classifyAccess(string fieldModifier,
                                 string accessorContext) {

        if (fieldModifier == "private") {

            if (accessorContext == "SAME_CLASS")
                return "ALLOWED";

            return "DENIED";
        }

        if (fieldModifier == "default") {

            if (accessorContext == "SAME_CLASS" ||
                accessorContext == "SAME_PACKAGE")
                return "ALLOWED";

            return "DENIED";
        }

        if (fieldModifier == "protected") {

            if (accessorContext == "SAME_CLASS" ||
                accessorContext == "SAME_PACKAGE" ||
                accessorContext == "SUBCLASS_DIFFERENT_PACKAGE_OWN_TYPE")
                return "ALLOWED";

            return "DENIED";
        }

        if (fieldModifier == "public") {
            return "ALLOWED";
        }

        return "DENIED";
    }


    static string describeContext(string accessorContext) {

        stringstream ss(accessorContext);
        string word;
        string result;

        while (getline(ss, word, '_')) {

            if (!word.empty()) {
                word[0] = toupper(word[0]);

                for (int i = 1; i < word.length(); i++)
                    word[i] = tolower(word[i]);

                if (!result.empty())
                    result += " ";

                result += word;
            }
        }

        return result;
    }
};


int main() {

    cout << AccessRuleEngine::classifyAccess(
        "protected",
        "SUBCLASS_DIFFERENT_PACKAGE_OWN_TYPE"
    ) << endl;

    cout << AccessRuleEngine::classifyAccess(
        "protected",
        "SUBCLASS_DIFFERENT_PACKAGE_PARENT_TYPE"
    ) << endl;

    cout << AccessRuleEngine::describeContext(
        "SUBCLASS_DIFFERENT_PACKAGE_PARENT_TYPE"
    ) << endl;

    return 0;
}