// Specification file for Student class
//
//  Student.hpp
//
//  Trinh Nguyen
//  February 26, 2017
//  Homework #4
//  IDE: Xcode

#ifndef _STUDENT
#define _STUDENT

#include <string>
#include <ostream>
using namespace std;

class Student
{
private:
	string name;
	double gpa;
	int id;
public:
	Student() { name = ""; gpa = 0.0; id = 0; }
	Student(string name, double gpa, int id) { this->name = name; this->gpa = gpa; this->id = id; }
	void setName(string name) { this->name = name; }
	void setID(int id) { this->id = id; }
	void setGPA(double gpa) { this->gpa = gpa; }
	string getName() { return name; }
	double getGPA() { return gpa; }
	int getID() { return id; }
	bool operator==(Student right)
	{
		if (id == right.getID()) return true;
		else return false;
	}
	bool operator<(Student right)
	{
		if (id < right.getID()) return true;
		else return false;
	}
	bool operator>(Student right)
	{
		if (id > right.getID()) return true;
		else return false;
	}
};


#endif 
