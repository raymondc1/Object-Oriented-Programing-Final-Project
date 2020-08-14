#include "Advisor.h"
#include "Student.h"
#include "FileIO.h"

Advisor::Advisor(string ID, string PWD, string room, string phone) : User(ID, PWD) {
	this->room = room;
	this->phone = phone;
}

string Advisor::get_room() { return room; }
string Advisor::get_phone() { return phone; }
vector<Student*> Advisor::get_advisees() { return advisees; }
vector<Student*> Advisor::get_all_students() { return all_students; }
vector<Advisor*> Advisor::get_all_advisors() { return all_advisors; }

void Advisor::add_advisses(Student* advisee) { advisees.push_back(advisee); }
void Advisor::add_all_students(Student* student) { all_students.push_back(student); }
void Advisor::add_all_advisors(Advisor* advisor) { all_advisors.push_back(advisor); }

//Overriding User::show_details()
void Advisor::show_details() {
	cout << "\n Advisor Details\n\n"
		 << "    ID: " << getID() << endl
		 << "  Room: " << get_room() << endl
		 << " Phone: " << get_phone() << endl;
}

//Overloading User::show_details()
void Advisor::show_details(Student* advisee) {
	cout << endl
		<< "    ID: " << advisee->getID() << endl
		<< " Major: " << advisee->get_major() << endl
		<< "   TEH: " << advisee->get_totalHours() << endl
		<< "   GPA: " << advisee->get_GPA() << endl;
}

string Advisor::get_current_time() {
	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	strftime(buffer, 80, "%m/%d/%Y", &timeinfo);
	return buffer;
}

string Advisor::create_note(string advisorID, string studentID, string note) {
	string tempNote;
	tempNote = "(" + advisorID + ' ' + get_current_time();
	tempNote += ") ";
	tempNote += studentID;
	tempNote += ' ';
	tempNote += note;
	FileIO::add_notes_to_advisingNotes(tempNote);
	return tempNote;
}

void Advisor::display_advisor_menu() {
	cout << "\n   " << getID() << " Advisor Menu\n\n"
		 << " a. Display all advisees\n"
		 << " b. Search for advisees\n"
		 << " c. View/Add advisee's note\n"
		 << " d. Add advisee to list\n"
		 << " e. Delete advisee from list\n"
		 << " f. Move collection of advisees to different advisor\n"
		 << " g. View other advisor's advisee\n"
		 << " h. Display all advisors\n"
		 << " i. View total amount of advisees in a major, and display average GPA\n"
		 << " j. Logout\n";
}

void Advisor::cout_all_advisees() {
	cout << endl << left << setw(7) << " ID" << setw(7) << " MAJOR" << setw(7) << " TEH" << endl;
	for (auto p : advisees) {
		cout << ' ' << left << setw(7) << p->getID() << setw(7) << p->get_major()
			<< setw(7) << p->get_totalHours() << endl;
	}
}

//Algorithm sort & Lambda Expression
void Advisor::display_all_advisees() {
	if (advisees.empty()) {
		system("CLS");
		cout << "\n No Advisees\n";
	}
	else {
		int condition = 0;
		while (!condition) {
			system("CLS");
			char choice = '0';
			cout << "\n Display All Advisees\n\n"
				 << " 1. Display by ID\n"
				 << " 2. Display by major\n"
				 << " 3. Display by total earned hours\n"
				 << "\n Input: ";
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			switch (choice) {
			case '1':
				sort(advisees.begin(), advisees.end(),
					[](const auto temp1, const auto temp2)->bool {return (temp1->getID() < temp2->getID()); });
				cout_all_advisees();
				condition = 1;
				break;
			case '2':
				sort(advisees.begin(), advisees.end(),
					[](const auto temp1, const auto temp2)->bool {return (temp1->get_major() < temp2->get_major()); });
				cout_all_advisees();
				condition = 1;
				break;
			case '3':
				sort(advisees.begin(), advisees.end(),
					[](const auto temp1, const auto temp2)->bool {return (temp1->get_totalHours() > temp2->get_totalHours()); });
				cout_all_advisees();
				condition = 1;
				break;
			default:
				cout << " Invalid Input\n"
					 << " Press Enter to try again";
				cin.get();
				break;
			}
		}
	}
}

void Advisor::search_for_advisees() {
	if (advisees.empty()) {
		system("CLS");
		cout << "\n No Advisees\n";
	}
	else {
		int condition = 0;
		while (!condition) {
			system("CLS");
			char choice = '0';
			int count = 0;
			string ID;
			string major;
			int upper_range;
			int lower_range;

			cout << "\n Search for Advisees\n\n"
				<< " 1. Search by ID\n"
				<< " 2. Search by major\n"
				<< " 3. Search by total earned hours\n"
				<< " 4. Search by major and total earned hours\n"
				<< "\n Input: ";
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			switch(choice) {
			case '1':
				cout << "\n Enter an ID: ";
				cin >> ID;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				for (auto p : advisees) {
					if (p->getID() == ID) {
						show_details(p);
						break;
					}
					if (p == advisees.back()) {
						cout << "\n No advisee of the ID " << ID << endl;
						break;
					}
				}
				condition = 1;
				break;
			case '2':
				cout << "\n Enter a major: ";
				cin >> major;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				for (auto p : advisees) {
					if (p->get_major() == major) {
						show_details(p);
						count++;
					}
					if (p == advisees.back() && count == 0) {
						cout << "\n No advisees of the major " << major << endl;
					}
				}
				condition = 1;
				break;
			case '3':
				cout << "\n Enter the upper range: ";
				cin >> upper_range;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\n Upper range must be a positive number\n"
						<< " Press Enter to try again";
					cin.get();
					break;
				}
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cout << " Enter the lower range: ";
				cin >> lower_range;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\n Lower range must be a positive number\n"
						<< " Press Enter to try again";
					cin.get();
					break;
				}
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				
				if (lower_range < 0) {
					cout << "\n Lower range can't be lower than 0\n"
						<< " Press Enter to try again";
					cin.get();
					break;
				}
				else if (upper_range < 0) {
					cout << "\n Upper range can't be lower than 0\n"
						<< " Press Enter to try again";
					cin.get();
					break;
				}
				else if (upper_range < lower_range) {
					cout << "\n Upper range must be higher than lower range\n"
						<< " Press Enter to try again";
					cin.get();
					break;
				}
				else {
					for (auto p : advisees) {
						if (p->get_totalHours() >= lower_range && p->get_totalHours() <= upper_range) {
							show_details(p);
							count++;
						}
						if (p == advisees.back() && count == 0) {
							cout << "\n No advisees between the range of " << lower_range << " and " << upper_range << endl;
						}
					}
				}
				condition = 1;
				break;
			case '4':
				cout << "\n Enter a major: ";
				cin >> major;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cout << " Enter the upper range: ";
				cin >> upper_range;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\n Upper range must be a positive number\n"
						<< " Press Enter to try again";
					cin.get();
					break;
				}
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cout << " Enter the lower range: ";
				cin >> lower_range;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\n Lower range must be a positive number\n"
						<< " Press Enter to try again";
					cin.get();
					break;
				}
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				
				if (lower_range < 0) {
					cout << "\n Lower range can't be lower than 0\n"
						<< " Press Enter to try again";
					cin.get();
					break;
				}
				else if (upper_range < 0) {
					cout << "\n Upper range can't be lower than 0\n"
						<< " Press Enter to try again";
					cin.get();
					break;
				}
				else if (upper_range < lower_range) {
					cout << "\n Upper range must be higher than lower range\n"
						<< " Press Enter to try again";
					cin.get();
					break;
				}
				else {
					for (auto p : advisees) {
						if (p->get_totalHours() >= lower_range && p->get_totalHours() <= upper_range && p->get_major() == major) {
							show_details(p);
							count++;
						}
						if (p == advisees.back() && count == 0) {
							cout << "\n No advisees of the major " << major
								<< " between the range of " << lower_range << " and " << upper_range << endl;
						}
					}
				}
				condition = 1;
				break;
			default:
				cout << " Invalid Input\n"
					<< " Press Enter to try again";
				cin.get();
				break;
			}
		}
	}
}

void Advisor::view_add_notes() {
	if (advisees.empty()) {
		system("CLS");
		cout << "\n No Advisees\n";
	}
	else {
		int condition = 0;
		while (!condition) {
			system("CLS");
			char choice = '0';
			string ID;
			string note;
			string tempNote;

			cout << "\n View or Add Advisee's Note\n\n"
				<< " 1. View an advisee's note\n"
				<< " 2. Add a note to an advisee\n"
				<< "\n Input: ";
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			switch(choice) {
			case '1':
				cout << "\n Enter an ID: ";
				cin >> ID;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				for (auto p : advisees) {
					if (p->getID() == ID) {
						if (p->get_Notes().empty()) {
							cout << "\n " << p->getID() << " has no advicing notes\n";
							break;
						}
						else {
							for (auto q : p->get_Notes()) {
								cout << endl << ' ' << q;
							}
							cout << endl;
							break;
						}
					}
					if (p == advisees.back()) {
						cout << "\n No advisee by the ID " << ID << endl;
						break;
					}
				}
				condition = 1;
				break;
			case '2':
				cout << "\n Enter an ID: ";
				cin >> ID;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				for (int i = 0; i < signed(advisees.size()); ++i) {
					if (advisees[i]->getID() == ID) {
						cout << " Enter note: ";
						getline(cin, note);
						tempNote = create_note(getID(), advisees[i]->getID(), note);
						advisees[i]->add_notes(tempNote);
						cout << " Note added to " << advisees[i]->getID() << endl;
						break;
					}
					if (i == signed(advisees.size() - 1)) {
						cout << "\n No advisee by the ID " << ID << endl;
						break;
					}
				}
				condition = 1;
				break;
			default:
				cout << " Invalid Input\n"
					<< " Press Enter to try again";
				cin.get();
				break;
			}
		}
	}
}

void Advisor::add_advisee_to_list() {
	int condition = 0;
	while (!condition) {
		system("CLS");
		char choice;
		string ID;
		string note = "***DOUBLE ADVISING REJECTED";
		string tempNote;

		cout << "\n Add Student to Advisee List\n\n"
			<< " Enter an ID: ";
		cin >> ID;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		for (int i = 0; i < signed(all_students.size()); ++i) {
			if (all_students[i]->getID() == ID) {
				if (all_students[i]->get_Advisor() == NULL) {
					show_details(all_students[i]);

					cout << "\n Would you like to add " << all_students[i]->getID() << " to your list?(y/n): ";
					cin >> choice;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					if (choice == 'y') {
						all_students[i]->set_advisor(this);
						add_advisses(all_students[i]);
						cout << ' ' << all_students[i]->getID() << " has been added to your list\n";
						condition = 1;
						break;
					}
					else if (choice == 'n') {
						cout << ' ' << all_students[i]->getID() << " was not added to your list\n";
						condition = 1;
						break;
					}
					else {
						cout << " Invalid Input. Failed to add " << all_students[i]->getID() << " to list\n";
						condition = 1;
						break;
					}
				}
				else if (all_students[i]->get_Advisor() == this) {
					cout << "\n " << note;
					tempNote = create_note(this->getID(), all_students[i]->getID(), note);
					all_students[i]->add_notes(tempNote);
					cout << "\n Added to advisee's note\n";
					condition = 1;
					break;
				}
				else {
					cout << "\n " << all_students[i]->getID() << " already has another advisor\n";
					condition = 1;
					break;
				}
			}
			if (i == signed(all_students.size() - 1)) {
				cout << "\n <ERROR> No such student!\n"
					<< " Press Enter to try again";
				cin.get();
				break;
			}
		}
	}
}

void Advisor::delete_advisee_from_list() {
	if (advisees.empty()) {
		system("CLS");
		cout << "\n No Advisees\n";
	}
	else {
		int condition = 0;
		while (!condition) {
			system("CLS");
			char choice;
			string ID;

			cout << "\n Delete Advisee From List\n\n"
				<< " Enter an ID: ";
			cin >> ID;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			for (int i = 0; i < signed(advisees.size()); ++i) {
				if (advisees[i]->getID() == ID) {
					show_details(advisees[i]);

					cout << "\n Are you sure you want to delete " << advisees[i]->getID() << " from the list?(y/n): ";
					cin >> choice;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					if (choice == 'y') {
						advisees[i]->set_advisor(NULL);
						advisees.erase(advisees.begin() + i);
						cout << ' ' << ID << " has been deleted from your list\n";
						condition = 1;
						break;
					}
					else if (choice == 'n') {
						cout << ' ' << advisees[i]->getID() << " was not deleted from your list\n";
						condition = 1;
						break;
					}
					else {
						cout << " Invalid Input. Failed to delete " << advisees[i]->getID() << " from list\n";
						condition = 1;
						break;
					}
				}
				if (i == signed(advisees.size() - 1)) {
					cout << "\n <ERROR> No such student!\n"
						<< " Press Enter to try again";
					cin.get();
					break;
				}
			}
		}
	}
}

void Advisor::move_collection() {
	if (advisees.empty()) {
		system("CLS");
		cout << "\n No Advisees\n";
	}
	else {
		int condition = 0;
		while (!condition) {
			system("CLS");
			int count = 0;
			string ID, major, code;
			string note, tempNote;
			const string key = "ENB#342";

			cout << "\n Move Advisee(s) to Another Advisor\n\n"
				<< " Enter an advisor ID: ";
			cin >> ID;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (ID == getID()) {
				cout << "\n You must enter an ID other than your own to request for a move\n"
					<< " Press Enter to try again";
				cin.get();
				continue;
			}
			for (int i = 0; i < signed(all_advisors.size()); ++i) {
				if (all_advisors[i]->getID() == ID) {
					cout << " Enter a major: ";
					cin >> major;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					cout << " Enter the authorization code: ";
					cin >> code;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					if (code == key) {
						for (int j = 0; j < signed(advisees.size()); ++j) {
							if (advisees[j]->get_major() == major) {
								advisees[j]->set_advisor(all_advisors[i]);
								all_advisors[i]->add_advisses(advisees[j]);
								note = "***ADVISOR CHANGED FROM " + this->getID() + " TO " + all_advisors[i]->getID();
								tempNote = create_note(this->getID(), advisees[j]->getID(), note);
								advisees[j]->add_notes(tempNote);
								cout << ' ' << advisees[j]->getID() << ' ' << note << endl;
								advisees.erase(advisees.begin() + j);
								count++;
								j--;
							}
						}
						if (count == 0) {
							cout << "\n No advisees with the major " << major << " was found\n";
						}
					}
					else {
						cout << "\n Failed to authorize move\n";
					}
					condition = 1;
					break;
				}
				if (i == signed(all_advisors.size()) - 1) {
					cout << "\n No advisor with the ID " << ID << " was found\n"
					<< " Press Enter to try again";
					cin.get();
					break;
				}
			}
		}
	}
}

void Advisor::view_other_advisor_advisee() {
	system("CLS");
	string ID;
	cout << "\n View Other Advisor's Advisee\n\n"
		<< " Enter an ID: ";
	cin >> ID;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	for (auto p : advisees) {
		if (p->getID() == ID) {
			cout << "\n " << p->getID() << " is your advisee. Please use option b to see advisee's detail\n";
			return;
		}
	}
	for (auto q : all_students) {
		if (q->getID() == ID) {
			if (q->get_Advisor() == NULL) {
				cout << "\n " << q->getID() << " does not have an advisor\n";
				return;
			}
			else {
				cout << "\n " << q->getID() << " is " << q->get_Advisor()->getID() << "'s advisee\n";
				return;
			}
		}
	}
	cout << "\n No student with the ID " << ID << " was found\n";
	return;
}

//Function Template & Algorithm for_each
template<typename T>
void display(T value) {
	cout << ' ' << value->getID() << endl;
}
void Advisor::display_all_advisors() {
	system("CLS");
	cout << "\n All Advisors\n\n";
	for_each(all_advisors.begin(), all_advisors.end(), display<Advisor*>);
}

void Advisor::major_amount_average_gpa() {
	if (advisees.empty()) {
		system("CLS");
		cout << "\n No advisees\n";
	}
	else {
		system("CLS");
		int count = 0;
		double total = 0;
		double average;
		string major;

		cout << "\n Major Amount & Average GPA\n\n"
			<< " Enter a major: ";
		cin >> major;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		for (auto p : advisees) {
			if (p->get_major() == major) {
				total += p->get_GPA();
				count++;
			}
		}
		if (count == 0) {
			cout << "\n No advisees with the major " << major << " was found\n";
			return;
		}
		else {
			average = total / count;
			average = round(average * 1000) / 1000;
			cout << "\n You have a total of " << count << ' ' << major << " major advisee(s)\n"
				<< " The average GPA among these advisee(s) is " << fixed << setprecision(2) << average << endl;
			return;
		}
	}
}

void Advisor::process_menu() {
	char input = '0';

	while (input != 'j') {
		system("CLS");
		display_advisor_menu();
		cout << "\n Input: ";
		cin >> input;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (input) {
		case 'a':
			display_all_advisees();
			cout << "\n Press Enter to continue";
			cin.get();
			break;
		case 'b':
			search_for_advisees();
			cout << "\n Press Enter to continue";
			cin.get();
			break;
		case 'c':
			view_add_notes();
			cout << "\n Press Enter to continue";
			cin.get();
			break;
		case 'd':
			add_advisee_to_list();
			cout << "\n Press Enter to continue";
			cin.get();
			break;
		case 'e':
			delete_advisee_from_list();
			cout << "\n Press Enter to continue";
			cin.get();
			break;
		case 'f':
			move_collection();
			cout << "\n Press Enter to continue";
			cin.get();
			break;
		case 'g':
			view_other_advisor_advisee();
			cout << "\n Press Enter to continue";
			cin.get();
			break;
		case 'h':
			display_all_advisors();
			cout << "\n Press Enter to continue";
			cin.get();
			break;
		case 'i':
			major_amount_average_gpa();
			cout << "\n Press Enter to continue";
			cin.get();
			break;
		case 'j':
			cout << " Logging off";
			cin.get();
			break;
		default:
			break;
		}
	}
}
