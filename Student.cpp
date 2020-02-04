#include "Advisor.h"
#include "Student.h"

Student::Student(string ID, string PWD, string major, int totalHours, double GPA) : User(ID, PWD) {
	this->major = major;
	this->totalHours = totalHours;
	this->GPA = GPA;
}

string Student::get_major() { return major; }
int Student::get_totalHours() { return totalHours; }
double Student::get_GPA() { return GPA; }
vector<string> Student::get_Notes() { return notes; }
Advisor* Student::get_Advisor() { return advisor; }

void Student::set_GPA(double GPA) { this->GPA = GPA; }
void Student::set_major(string major) { this->major = major; }
void Student::set_totalHours(int totalHours) { this->totalHours = totalHours; }
void Student::add_notes(string notes) { this->notes.push_back(notes); }
void Student::set_advisor(Advisor* advisor) { this->advisor = advisor; }

//Overriding User::show_details()
void Student::show_details() {
	cout << "\n Student Details\n\n"
		 << "    ID: " << getID() << endl
		 << " Major: " << get_major() << endl
		 << "   TEH: " << get_totalHours() << endl
		 << "   GPA: " << get_GPA() << endl;
}

//Polymorphism
void Student::polymorphism_details(User& user) {
	user.show_details();
}

void Student::display_student_menu() {
	cout << "\n   " << getID()  << " Student Menu\n\n"
		<< " a. Display Advisor Details\n"
		<< " b. View GPA, Major, and Total Hours\n"
		<< " c. Update GPA, Major, or Total Hours\n"
		<< " d. Logout\n";
}

void Student::display_advisor_details() {
	if (advisor == NULL) {
		system("CLS");
		cout << "\n No Advisor\n";
	}
	else {
		system("CLS");
		polymorphism_details(*advisor);
	}
}

void Student::view_student_details() {
	system("CLS");
	polymorphism_details(*this);
}

void Student::updata_student_details() {
	int condition = 0;

	while (!condition) {
		system("ClS");
		char choice = '0';
		char _continue = '0';
		string major;
		int totalHours;
		double GPA;

		cout << "\n Update Details\n\n"
			<< " 1. Update Major\n"
			<< " 2. Update Total Hours\n"
			<< " 3. Update GPA\n"
			<< "\n Input: ";
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (choice) {
		case '1':
			cout << "\n Enter new Major: ";
			cin >> major;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			set_major(major);

			cout << "\n Major has been updated to " << get_major() << endl
				<< "\n Update another element?(y/n): ";
			cin >> _continue;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (_continue == 'n') {
				condition = 1;
				break;
			}
			else if (_continue == 'y') {
				break;
			}
			else {
				cout << " Invalid Input. Failed to Update another element\n";
				condition = 1;
				break;
			}
		case '2':
			cout << "\n Enter new Total Hours: ";
			cin >> totalHours;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\n Total Hours must be a number\n"
					<< " Press Enter to try again";
				cin.get();
				break;
			}
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (totalHours < 0) {
				cout << "\n Total Hours can't be smaller than 0\n"
					<< " Press Enter to try again";
				cin.get();
				break;
			}

			set_totalHours(totalHours);

			cout << "\n Total Hours has been updated to " << get_totalHours() << endl
				<< "\n Update another element?(y/n): ";
			cin >> _continue;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (_continue == 'n') {
				condition = 1;
				break;
			}
			else if (_continue == 'y') {
				break;
			}
			else {
				cout << " Invalid Input. Failed to Update another element\n";
				condition = 1;
				break;
			}
		case '3':
			cout << "\n Enter new GPA: ";
			cin >> GPA;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\n GPA must be a number\n"
					<< " Press Enter to try again";
				cin.get();
				break;
			}
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (GPA < 0.0) {
				cout << "\n GPA can't be smaller than 0.0\n"
					<< " Press Enter to try again";
				cin.get();
				break;
			}
			if (GPA > 4.0) {
				cout << "\n GPA can't be bigger than 4.0\n"
					<< " Press Enter to try again";
				cin.get();
				break;
			}

			set_GPA(GPA);

			cout << "\n GPA has been updated to " << fixed << setprecision(2) << get_GPA() << endl
				<< "\n Update another element?(y/n): ";
			cin >> _continue;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (_continue == 'n') {
				condition = 1;
				break;
			}
			else if (_continue == 'y') {
				break;
			}
			else {
				cout << " Invalid Input. Failed to Update another element\n";
				condition = 1;
				break;
			}
		default:
			cout << " Invalid Input\n"
				<< " Press Enter to try again";
			cin.get();
			break;
		}
	}
}

void Student::process_menu() {
	char input = '0';

	while (input != 'd') {
		system("CLS");
		display_student_menu();
		cout << "\n Input: ";
		cin >> input;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (input) {
		case 'a':
			display_advisor_details();
			cout << "\n Press Enter to continue";
			cin.get();
			break;
		case 'b':
			view_student_details();
			cout << "\n Press Enter to continue";
			cin.get();
			break;
		case 'c':
			updata_student_details();
			cout << "\n Press Enter to continue";
			cin.get();
			break;
		case 'd':
			cout << " Logging off";
			cin.get();
			break;
		default:
			break;
		}
	}
}
