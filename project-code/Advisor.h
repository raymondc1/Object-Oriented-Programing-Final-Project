#ifndef ADVISOR_H
#define ADVISOR_H

#include "User.h"

class Student;

class Advisor : public User {
private:
	string room;
	string phone;
	vector<Student*> advisees;
	vector<Student*> all_students;
	vector<Advisor*> all_advisors;
public:
	Advisor() {}
	Advisor(string ID, string PWD, string room, string phone);

	string get_room();
	string get_phone();
	vector<Student*> get_advisees();
	vector<Student*> get_all_students();
	vector<Advisor*> get_all_advisors();

	void add_advisses(Student* advisee);
	void add_all_students(Student* student);
	void add_all_advisors(Advisor* advisor);

	void show_details();					//Overriding User::show_details()
	void show_details(Student* advisee);	//Overloading User::show_details()
	string get_current_time();
	string create_note(string advisorID, string studentID, string note);

	void display_advisor_menu();			//Algorithm sort & Lambda Expression
	void cout_all_advisees();
	void display_all_advisees();
	void search_for_advisees();
	void view_add_notes();
	void add_advisee_to_list();
	void delete_advisee_from_list();
	void move_collection();
	void view_other_advisor_advisee();
	void display_all_advisors();			//Function Template & Algorithm for_each
	void major_amount_average_gpa();
	void process_menu();
};

#endif
