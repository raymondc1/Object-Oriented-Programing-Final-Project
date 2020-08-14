#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <exception>

#include "User.h"

class FileNotFoundException : public exception {
public:
	virtual char const *what() {
		return "Failed to load file\n";
	}
};

#endif
