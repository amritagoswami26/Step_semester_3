#include <bits/stdc++.h>
using namespace std;

class Employee {
private:
    string empId;
    string empName;
    double salary;

public:
    Employee(string id, string name, double sal) {
        empId = id;
        empName = name;
        salary = sal;
    }

    virtual ~Employee() {}

    double getSalary() {
        return salary;
    }
};


class ManagerEmployee : public Employee {
private:
    double teamBonus;

public:
    ManagerEmployee(string id, string name,
                    double sal, double bonus)
        : Employee(id, name, sal) {

        teamBonus = bonus;
    }

    double effectiveSalary() {
        return getSalary() + teamBonus;
    }
};


class InternEmployee : public Employee {
private:
    double stipendCap;

public:
    InternEmployee(string id, string name,
                   double sal, double cap)
        : Employee(id, name, sal) {

        stipendCap = cap;
    }

    double effectiveSalary() {
        return min(getSalary(), stipendCap);
    }
};


int main() {

    Employee plain("E101", "Ravi", 40000);

    ManagerEmployee manager(
        "E102", "Divya", 70000, 8000
    );

    InternEmployee intern(
        "E103", "Meera", 12000, 10000
    );

    Employee* employees[3] = {
        &plain,
        &manager,
        &intern
    };

    for (int i = 0; i < 3; i++) {

        if (dynamic_cast<ManagerEmployee*>(employees[i])) {

            ManagerEmployee* m =
                dynamic_cast<ManagerEmployee*>(employees[i]);

            cout << "Manager effective pay: Rs "
                 << m->effectiveSalary() << endl;
        }

        else if (dynamic_cast<InternEmployee*>(employees[i])) {

            InternEmployee* in =
                dynamic_cast<InternEmployee*>(employees[i]);

            cout << "Intern effective pay: Rs "
                 << in->effectiveSalary() << endl;
        }

        else {
            cout << "Plain employee pay: Rs "
                 << employees[i]->getSalary() << endl;
        }
    }

    return 0;
}