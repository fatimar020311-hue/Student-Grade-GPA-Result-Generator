/*
 ==========================================================
   Student Grade & Result Generator  —  OOP Version
   OOP Concepts: Class, Object, Encapsulation, Inheritance,
                 Polymorphism, Constructor, Destructor,
                 Access Specifiers
 ==========================================================
*/

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

// ────────────────────────────────────────────────
// BASE CLASS  →  Class, Encapsulation, Constructor,
//                Destructor, Access Specifiers
// ────────────────────────────────────────────────
class Person {
protected:                     // protected: accessible in child class
    string name;
    int    rollNo;

public:                        // public: accessible everywhere

    // Constructor
    Person(string n, int r) {
        if (n.empty())
            throw invalid_argument("Name cannot be empty.");
        if (r <= 0)
            throw invalid_argument("Roll number must be a positive integer.");
        name   = n;
        rollNo = r;
    }

    // Destructor
    ~Person() { }

    // Getter methods  (Encapsulation)
    string getName() { return name;   }
    int    getRoll() { return rollNo; }

    // virtual → enables Polymorphism (overriding in child)
    virtual void display() {
        cout << "Name   : " << name   << endl;
        cout << "Roll No: " << rollNo << endl;
    }
};

// ────────────────────────────────────────────────
// DERIVED CLASS  →  Inheritance, Polymorphism,
//                   Constructor Chaining
// ────────────────────────────────────────────────
class Student : public Person {   // Inheritance (Student IS-A Person)

private:                          // private: only inside this class
    int subjects;
    int totalObtained;
    int totalMax;

public:
    // Constructor chaining → calls Person's constructor
    Student(string n, int r, int s) : Person(n, r) {
        if (s <= 0)
            throw invalid_argument("Number of subjects must be a positive integer.");
        subjects      = s;
        totalObtained = 0;
        totalMax      = 0;
    }

    // Add one subject's marks  (Encapsulation)
    void addSubject(string subName, int obtained, int maxMarks) {
        if (subName.empty())
            throw invalid_argument("Subject name cannot be empty.");
        if (maxMarks <= 0)
            throw invalid_argument("Total marks must be a positive integer.");
        if (obtained < 0)
            throw invalid_argument("Marks obtained cannot be negative.");
        if (obtained > maxMarks)
            throw invalid_argument("Marks obtained cannot exceed total marks.");

        cout << "  [" << subName << "]  "
             << obtained << " / " << maxMarks << "\n";
        totalObtained += obtained;
        totalMax      += maxMarks;
    }

    // Helper functions  (Encapsulation: internal logic hidden)
    float getPercentage() {
        return (totalMax == 0) ? 0 : (totalObtained * 100.0f / totalMax);
    }

    string getGrade() {
        float p = getPercentage();
        if (p >= 90) return "A+";
        if (p >= 80) return "A";
        if (p >= 70) return "B";
        if (p >= 60) return "C";
        if (p >= 40) return "D";
        return "F";
    }

    float getGPA() {
        float p = getPercentage();
        if (p >= 90) return 4.0f;
        if (p >= 80) return 3.7f;
        if (p >= 70) return 3.0f;
        if (p >= 60) return 2.0f;
        if (p >= 40) return 1.0f;
        return 0.0f;
    }

    string getStatus() {
        return (getPercentage() >= 40) ? "PASS" : "FAIL";
    }

    // Polymorphism: overrides Person::display()
    void display() override {
        float p = getPercentage();
        cout << "\n==============================\n";
        cout << "      STUDENT RESULT CARD      \n";
        cout << "==============================\n";
        Person::display();         // calls base class version
        cout << "------------------------------\n";
        cout << "Total   : " << totalObtained << "/" << totalMax << endl;
        cout << "Percent : " << p             << "%" << endl;
        cout << "Grade   : " << getGrade()          << endl;
        cout << "GPA     : " << getGPA()            << endl;
        cout << "Status  : " << getStatus()         << endl;
        cout << "==============================\n";
    }
};

// ────────────────────────────────────────────────
// MAIN  →  Object Creation, Program Entry
// ────────────────────────────────────────────────
int main() {
    string name, subName;
    int    roll, numSubjects, obtained, maxMarks;

    try {
        cout << "Enter Student Name  : ";
        getline(cin, name);
        cout << "Enter Roll Number   : ";
        if (!(cin >> roll))
            throw invalid_argument("Roll number must be a valid integer.");
        cout << "Number of Subjects  : ";
        if (!(cin >> numSubjects))
            throw invalid_argument("Number of subjects must be a valid integer.");
        cin.ignore();

        // Object creation  (Class instantiation)
        Student s(name, roll, numSubjects);

        cout << "\n--- Enter Subject Marks ---\n";
        for (int i = 1; i <= numSubjects; i++) {
            cout << "\nSubject " << i << " Name   : ";
            getline(cin, subName);
            cout << "Marks Obtained   : ";
            if (!(cin >> obtained))
                throw invalid_argument("Marks obtained must be a valid integer.");
            cout << "Total Marks      : ";
            if (!(cin >> maxMarks))
                throw invalid_argument("Total marks must be a valid integer.");
            cin.ignore();
            s.addSubject(subName, obtained, maxMarks);
        }

        // Polymorphism: Student::display() runs, not Person::display()
        s.display();

    } catch (const invalid_argument& e) {
        cerr << "\n[Input Error] " << e.what() << endl;
        return 1;
    } catch (const exception& e) {
        cerr << "\n[Error] " << e.what() << endl;
        return 1;
    } catch (...) {
        cerr << "\n[Unknown Error] An unexpected error occurred." << endl;
        return 1;
    }

    return 0;
}
