#include <iostream>
#include <map>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    // Grade → Point mapping
    map<string, double> gradePoint = {
        {"A+", 4.0}, {"A", 3.75}, {"A-", 3.5},
        {"B+", 3.25}, {"B", 3.0}, {"B-", 2.75},
        {"C+", 2.5}, {"C", 2.25}, {"D", 2.0},
        {"F", 0.0}
    };

    int semesters;
    cout << "Enter number of semesters: ";
    cin >> semesters;

    double totalAllPoints = 0;
    double totalAllCredits = 0;

    for(int s = 1; s <= semesters; s++) {
        cout << "\n===== Semester " << s << " =====\n";

        int courses;
        cout << "Enter number of courses: ";
        cin >> courses;

        double semesterPoints = 0;
        double semesterCredits = 0;

        vector<string> grades;
        vector<double> creditsList;

        for(int i = 1; i <= courses; i++) {
            string grade;
            double credits;

            cout << "\nCourse " << i << endl;
            cout << "Enter Grade: ";
            cin >> grade;
            cout << "Enter Credit Hours: ";
            cin >> credits;

            if(gradePoint.find(grade) == gradePoint.end()) {
                cout << "Invalid grade! Course skipped.\n";
                continue;
            }

            double points = gradePoint[grade] * credits;
            semesterPoints += points;
            semesterCredits += credits;

            grades.push_back(grade);
            creditsList.push_back(credits);
        }

        cout << "\n--- Course Summary ---\n";
        for(size_t i = 0; i < grades.size(); i++) {
            cout << "Course " << i+1 << ": Grade " << grades[i]
                 << ", Credits " << creditsList[i] << endl;
        }

        double semesterGPA = semesterPoints / semesterCredits;
        cout << fixed << setprecision(2);
        cout << "Semester GPA: " << semesterGPA << endl;

        totalAllPoints += semesterPoints;
        totalAllCredits += semesterCredits;
    }

    double CGPA = totalAllPoints / totalAllCredits;
    cout << "\n=============================\n";
    cout << "FINAL CGPA: " << CGPA << endl;
    cout << "=============================\n";

    return 0;
}

