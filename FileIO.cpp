#include "FileIO.h"
#include "MyException.h"

void FileIO::read_Data_students(vector<Student> &Students) {
	ifstream ifile("C:\\3331\\Project2\\Data_students.txt");
	if (ifile) {
		string line;
		string data;
		stringstream ss;
		string ID, PWD, major;
		int totalHours;
		double GPA;

		while (getline(ifile, line)) {
			ss.str(line);
			ss.clear();

			getline(ss, data, ',');
			ID = data;
			getline(ss, data, ',');
			PWD = data;
			getline(ss, data, ',');
			major = data;
			getline(ss, data, ',');
			totalHours = stoi(data);
			getline(ss, data, ',');
			GPA = stod(data);

			Student temp(ID, PWD, major, totalHours, GPA);
			Students.push_back(temp);
		}
	}
	else {
		FileNotFoundException myex;
		throw myex;
	}
	ifile.close();
}

void FileIO::read_Data_advisingNotes(vector<Student> &Students) {
	ifstream ifile("C:\\3331\\Project2\\Data_advisingNotes.txt");
	if (ifile) {
		string line;
		string data;
		stringstream ss;

		while (getline(ifile, line)) {
			ss.str(line);
			ss.clear();

			getline(ss, data, ' ');
			getline(ss, data, ' ');
			getline(ss, data, ' ');
			for (int i = 0; i < signed(Students.size()); ++i) {
				if (Students[i].getID() == data) {
					Students[i].add_notes(line);
					break;
				}
			}
		}
	}
	else {
		FileNotFoundException myex;
		throw myex;
	}
	ifile.close();
}

void FileIO::read_Data_advisors(vector<Advisor> &Advisors) {
	ifstream ifile("C:\\3331\\Project2\\Data_advisors.txt");
	if (ifile) {
		string line;
		string data;
		stringstream ss;
		string ID, PWD, room, phone;

		while (getline(ifile, line)) {
			ss.str(line);
			ss.clear();

			getline(ss, data, ',');
			ID = data;
			getline(ss, data, ',');
			PWD = data;
			getline(ss, data, ',');
			room = data;
			getline(ss, data, ',');
			phone = data;

			Advisor temp(ID, PWD, room, phone);
			Advisors.push_back(temp);
		}
	}
	else {
		FileNotFoundException myex;
		throw myex;
	}
	ifile.close();
}

void FileIO::read_Data_advisees(vector<Advisor> &Advisors, vector<Student> &Students) {
	ifstream ifile("C:\\3331\\Project2\\Data_advisees.txt");
	if (ifile) {
		string line;
		string data;
		string student;
		string advisor;
		stringstream ss;

		while (getline(ifile, line)) {
			ss.str(line);
			ss.clear();

			getline(ss, data, ',');
			advisor = data;
			while (getline(ss, data, ',')) {
				for (int i = 0; i < signed(Advisors.size()); i++) {
					if (Advisors[i].getID() == advisor) {
						for (int j = 0; j < signed(Students.size()); j++) {
							if (Students[j].getID() == data) {
								Students[j].set_advisor(&Advisors[i]);
								Advisors[i].add_advisses(&Students[j]);
							}
						}
					}
				}
			}
		}
	}
	else {
		FileNotFoundException myex;
		throw myex;
	}
	ifile.close();
}

void FileIO::addingDataToAdvisor(vector<Advisor> &Advisors, vector<Student> &Students) {
	for (int i = 0; i < signed(Advisors.size()); ++i) {
		for (int j = 0; j < signed(Advisors.size()); ++j) {
			Advisors[i].add_all_advisors(&Advisors[j]);
		}
		for (int k = 0; k < signed(Students.size()); ++k) {
			Advisors[i].add_all_students(&Students[k]);
		}
	}
}

void FileIO::add_notes_to_advisingNotes(string tempNote) {
	ofstream ofile("C:\\3331\\Project2\\Data_advisingNotes.txt", ios::app);
	ofile << tempNote << endl;
	ofile.close();
}

void FileIO::write_Data_advisees(vector<Advisor> &Advisors) {
	ofstream ofile("C:\\3331\\Project2\\Data_advisees.txt");
	for (auto p : Advisors) {
		ofile << p.getID();
		if (p.get_advisees().empty()) {
			ofile << endl;
		}
		else {
			for (auto q : p.get_advisees()) {
				ofile << ',' << q->getID();
			}
			ofile << endl;
		}
	}
	ofile.close();
}

void FileIO::write_Data_students(vector<Student> &Students) {
	ofstream ofile("C:\\3331\\Project2\\Data_students.txt");
	for (auto p : Students) {
		ofile << p.getID() << ','
			  << p.getPWD() << ','
			  << p.get_major() << ','
			  << p.get_totalHours() << ','
			  << p.get_GPA() << endl;
	}
	ofile.close();
}
