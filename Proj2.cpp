#include "User.h"
#include "Advisor.h"
#include "Student.h"
#include "FileIO.h"
#include "MyException.h"

int main()
{
	vector<Advisor> Advisors;
	vector<Student> Students;

	FileIO data;

	//Exception Handling
	try {
		data.read_Data_students(Students);
		data.read_Data_advisingNotes(Students);
		data.read_Data_advisors(Advisors);
		data.read_Data_advisees(Advisors, Students);
		data.addingDataToAdvisor(Advisors, Students);

		char input;

		while (true) {
			system("CLS");
			cout << "\n   School System"
				<< "\n\n 1. Advisor menu"
				<< "\n 2. Student menu"
				<< "\n 3. Exit"
				<< "\n\n Input: ";
			cin >> input;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (input == '1') {
				int match = 0;
				while (!match) {
					system("CLS");
					char input;
					string ID_input;
					string PWD_input;
					cout << "\n Advisor Login"
						<< "\n\n  ID: ";
					cin >> ID_input;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					cout << " PWD: ";
					cin >> PWD_input;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					for (int i = 0; i < signed(Advisors.size()); ++i) {
						if (Advisors[i].getID() == ID_input) {
							if (Advisors[i].getPWD() == PWD_input) {
								Advisors[i].process_menu();
								data.write_Data_advisees(Advisors);
								match = 1;
								break;
							}
							else {
								cout << "\n PWD does not match"
									<< "\n Continue?(y/n): ";
								cin >> input;
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								if (input == 'n') {
									match = 1;
									break;
								}
								else if (input == 'y') {
									break;
								}
								else {
									cout << " Invalid input"
										<< "\n Press Enter to conintue";
									cin.get();
									break;
								}
							}
						}
						if (i == Advisors.size() - 1) {
							cout << "\n No advisor was found using the ID " << ID_input
								<< "\n Continue?(y/n): ";
							cin >> input;
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							if (input == 'n') {
								match = 1;
								break;
							}
							else if (input == 'y') {
								break;
							}
							else {
								cout << " Invalid input"
									<< "\n Press Enter to conintue";
								cin.get();
								break;
							}
						}
					}
				}
			}
			if (input == '2') {
				int match = 0;
				while (!match) {
					system("CLS");
					char input;
					string ID_input;
					string PWD_input;
					cout << "\n Student Login"
						<< "\n\n  ID: ";
					cin >> ID_input;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					cout << " PWD: ";
					cin >> PWD_input;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					for (int i = 0; i < signed(Students.size()); ++i) {
						if (Students[i].getID() == ID_input) {
							if (Students[i].getPWD() == PWD_input) {
								Students[i].process_menu();
								data.write_Data_students(Students);
								match = 1;
								break;
							}
							else {
								cout << "\n PWD does not match"
									<< "\n Continue?(y/n): ";
								cin >> input;
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								if (input == 'n') {
									match = 1;
									break;
								}
								else if (input == 'y') {
									break;
								}
								else {
									cout << " Invalid input"
										<< "\n Press Enter to conintue";
									cin.get();
									break;
								}
							}
						}
						if (i == Students.size() - 1) {
							cout << "\n No student was found using the ID " << ID_input
								<< "\n Continue?(y/n): ";
							cin >> input;
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							if (input == 'n') {
								match = 1;
								break;
							}
							else if (input == 'y') {
								break;
							}
							else {
								cout << " Invalid input"
									<< "\n Press Enter to conintue";
								cin.get();
								break;
							}
						}
					}
				}
			}
			if (input == '3') {
				cout << " Bye!"
					<< "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
				break;
			}
		}
	}
	catch (FileNotFoundException e) {
		cout << e.what();
	}

	return 0;
}
