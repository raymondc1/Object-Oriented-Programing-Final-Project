#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"

class Advisor;

class Student : public User {
private:
	string major;
	int totalHours;
	double GPA;
	vector<string> notes;
	Advisor* advisor;
public:
	Student() {}
	Student(string ID, string PWD, string major, int totalHours, double GPA);

	string get_major();
	int get_totalHours();
	double get_GPA();
	vector<string> get_Notes();
	Advisor* get_Advisor();

	void set_GPA(double GPA);
	void set_major(string major);
	void set_totalHours(int totalHours);
	void add_notes(string notes);
	void set_advisor(Advisor* advisor);

	void show_details();					//Overriding User::show_details()
	void polymorphism_details(User& user);	//Polymorhpism

	void display_student_menu();
	void display_advisor_details();
	void view_student_details();
	void updata_student_details();
	void process_menu();
};

#endif
