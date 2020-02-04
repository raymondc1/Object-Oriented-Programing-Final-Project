#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <cmath>

using namespace std;

class User {
private:
	string ID;
	string PWD;
public:
	User() {}
	User(string ID, string PWD);

	string getID();
	string getPWD();

	virtual void show_details() = 0;
};

#endif
