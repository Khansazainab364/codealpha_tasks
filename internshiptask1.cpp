#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Course {
    string grade;
    int credit;
};

// Convert string to uppercase
string makeUpper(string s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}

// Grade map
double gradeToPoint(string g) {
    static map<string, double> gp = {
        {"A+",4.0},{"A",4.0},{"A-",3.7},
        {"B+",3.3},{"B",3.0},{"B-",2.7},
        {"C+",2.3},{"C",2.0},{"C-",1.7},
        {"D",1.0},{"F",0.0}
    };

    g = makeUpper(g);
    if (gp.count(g)) return gp[g];
    return -1;
}

// Input one semester
vector<Course> readSemester(int semNo) {
    int n;
    cout << "\nEnter courses in semester " << semNo << ": ";
    cin >> n;

    vector<Course> list(n);

    for (int i = 0; i < n; i++) {
        cout << "\nCourse #" << i + 1 << endl;

        // Grade input
        while (true) {
            cout << "Grade: ";
            cin >> list[i].grade;

            if (gradeToPoint(list[i].grade) != -1)
                break;
            cout << "Invalid grade, try again!\n";
        }

        // Credit input
        while (true) {
            cout << "Credit hours: ";
            cin >> list[i].credit;

            if (list[i].credit > 0)
                break;
            cout << "Must be positive!\n";
        }
    }

    return list;
}

// Calculate GPA + totals together
void computeResult(const vector<Course>& courses,
                   double &points, int &credits, double &gpa) {

    points = 0;
    credits = 0;

    for (auto &c : courses) {
        double gp = gradeToPoint(c.grade);
        points += gp * c.credit;
        credits += c.credit;
    }

    gpa = (credits == 0) ? 0 : points / credits;
}

// Display semester
void showSemester(int semNo, const vector<Course>& courses,
                  double gpa, int credits, double points) {

    cout << "\n--- Semester " << semNo << " ---\n";

    for (int i = 0; i < courses.size(); i++) {
        cout << "Course " << i + 1
             << " | " << makeUpper(courses[i].grade)
             << " | Credit: " << courses[i].credit << endl;
    }

    cout << fixed << setprecision(2);
    cout << "Credits: " << credits << endl;
    cout << "Points: " << points << endl;
    cout << "GPA: " << gpa << endl;
}

int main() {
    int totalSem;
    cout << "How many semesters? ";
    cin >> totalSem;

    vector<vector<Course>> allSem(totalSem);

    double grandPoints = 0;
    int grandCredits = 0;

    for (int i = 0; i < totalSem; i++) {
        allSem[i] = readSemester(i + 1);

        double pts, gpa;
        int creds;

        computeResult(allSem[i], pts, creds, gpa);

        showSemester(i + 1, allSem[i], gpa, creds, pts);

        grandPoints += pts;
        grandCredits += creds;
    }

    double cgpa = (grandCredits == 0) ? 0 : grandPoints / grandCredits;

    cout << "\n====== FINAL ======\n";
    cout << fixed << setprecision(2);
    cout << "Total Credits: " << grandCredits << endl;
    cout << "Total Points: " << grandPoints << endl;
    cout << "CGPA: " << cgpa << endl;

    return 0;
}