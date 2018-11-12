/*******************************************************************************
* Name : student.cpp
* Author: Mathew Seedhom
* Date: Sep 10, 2018
* Description: 
* Pledge: I pledge my honor that I have abided by the Stevens Honor System.
******************************************************************************/
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Student {

public:
    // Constructor that uses an initializer list.
    Student(string first, string last, float gpa, int id) : first_{first}, last_{last}, gpa_{gpa}, id_{id} { }

    string full_name() const{
    	//Returns a String for someone's full name
    	return first_ + " " + last_;
    }

    float gpa() const{
    	//Returns a float of someone's GPA
    	return gpa_;
    }

    int id() const{
    	//Returns an integer of someone's ID number
    	return id_;
    }

    void print_info() const{
    	//Prints someone's full name, GPA, and ID number
    	cout << full_name() << ", GPA: " << fixed << setprecision(2) << gpa() << ", ID: " << id() << endl;
    }

private:
    // Member variables (fields). Use the trailing _ for these variables.
    string first_, last_;
    float gpa_;
    int id_;

};

/**
     * Takes a vector of Student objects, and returns a new vector
     * With all Students whose GPA is < 1.0.
     */
    vector<Student> find_failing_students(const vector<Student> &students){
    	//Iterates through the students vector, appending each student whose gpa is
    	//less than 1.0 to the failing_students vector.
    	vector<Student> failing_students;
    	for (const auto &student :students){
    		if (student.gpa() < 1.0){
    			failing_students.push_back(student);
    		}
    	}
    	return failing_students;
    }

    void print_students(const vector<Student> &students){
    	//Takes a vector of Student objects and prints them to the screen.
    	for (const auto &student :students){
    		student.print_info();
    	}
    }
/*
 * Allows the user to enter information for the multiple students, then
 * find those students whose GPA is below 1.0 and prints them to the
 * screen.
 */
int main() {
	string first_name, last_name; float gpa;
	int id;
	char repeat;
	vector<Student> students;
		do {
			cout << "Enter student's first name: ";
			cin >> first_name;
			cout << "Enter student's last name: ";
			cin >> last_name;
			gpa = -1;
			while (gpa < 0 || gpa > 4) {
				cout << "Enter student's GPA (0.0-4.0): ";
				cin >> gpa;
			}
		cout << "Enter student's ID: ";
		cin >> id;
		students.push_back(Student(first_name, last_name, gpa, id));
		cout << "Add another student to database (Y/N)? ";
		cin >> repeat;
	} while (repeat == 'Y' || repeat == 'y');

	cout << endl << "All students:" << endl;
	print_students(students);

	cout << endl << "Failing students:";
	// TODO
	// Print a space and the word 'None' on the same line if no students are // failing.
	// Otherwise, print each failing student on a separate line.
	vector<Student> fail = find_failing_students(students);
	if (fail.empty()){
		cout << " None";
	} else {
		cout << endl;
		print_students(fail);
	}
	return 0;
}
