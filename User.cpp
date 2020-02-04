#include "User.h"

User::User(string ID, string PWD) {
	this->ID = ID;
	this->PWD = PWD;
}

string User::getID() { return ID; }
string User::getPWD() { return PWD; }
