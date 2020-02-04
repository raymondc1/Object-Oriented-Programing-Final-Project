#ifndef FILEIO_H
#define FILEIO_H

#include <iostream>
#include <fstream>
#include <sstream>

#include "Advisor.h"
#include "Student.h"

class FileIO {
public:
	FileIO() {}
	void read_Data_students(vector<Student> &Students);
	void read_Data_advisingNotes(vector<Student> &Students);
	void read_Data_advisors(vector<Advisor> &Advisors);
	void read_Data_advisees(vector<Advisor> &Advisors, vector<Student> &Students);

	void addingDataToAdvisor(vector<Advisor> &Advisors, vector<Student> &Students);
	static void add_notes_to_advisingNotes(string tempNote);

	void write_Data_advisees(vector<Advisor> &Advisors);
	void write_Data_students(vector<Student> &Students);
};

#endif
