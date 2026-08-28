#include <bits/stdc++.h>
using namespace std;

class BookIssue {
private:
    string title;
    string borrowerName;
    int daysOverdue;

public:
    BookIssue(string t, string b, int d) {
        title = t;
        borrowerName = b;
        daysOverdue = d;
    }

    // Instance method
    double fineAmount() {
        if (daysOverdue > 0)
            return daysOverdue * 5;
        else
            return 0;
    }

    // Instance method
    bool isSeverelyOverdue() {
        return daysOverdue > 14;
    }

    string getTitle() {
        return title;
    }

    int getDaysOverdue() {
        return daysOverdue;
    }

    /*
    totalFineCollected is static because it calculates
    the total fine of multiple BookIssue objects.
    fineAmount is not static because it works on the
    data of one particular book.
    */
    static double totalFineCollected(BookIssue issues[], int size) {
        double total = 0;

        for (int i = 0; i < size; i++) {
            total += issues[i].fineAmount();
        }

        return total;
    }
};

int main() {
    BookIssue issues[5] = {
        BookIssue("Clean Code", "Ravi", 18),
        BookIssue("Effective Java", "Anitha", 5),
        BookIssue("Refactoring", "Karthik", 0),
        BookIssue("DSA Handbook", "Meera", 21),
        BookIssue("Design Patterns", "Suresh", 9)
    };

    for (int i = 0; i < 5; i++) {
        cout << issues[i].getTitle()
             << " - "
             << issues[i].getDaysOverdue()
             << " days - ";

        if (issues[i].isSeverelyOverdue())
            cout << "Severely overdue";
        else
            cout << "OK";

        cout << endl;
    }

    cout << fixed << setprecision(1);

    cout << "Total fine collected: Rs "
         << BookIssue::totalFineCollected(issues, 5)
         << endl;

    return 0;
}