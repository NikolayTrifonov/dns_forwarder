/**
 * @file IOColor.cpp
 * @version 1.0
 * @author Nikolay Trifonov
 *
 * @brief The file represents the implementation of the input-output color's scheme.
 */

#include <iostream>
#include <string.h>
using namespace std;

#include "../../include/IOColor.h"

namespace DFNS {

	// CONSTRUCTORS
	IOColor::IOColor(Codes code) : code(code) {
	}

	// DESTRUCTOR
	IOColor::~IOColor() {
	}

	// OVERLOADED OPERATORS
	std::ostream& operator<<(std::ostream& os, const IOColor& ioColor) {
		return os << "\033[" << ioColor.code  << "m";
	}

	string& operator+(string& str, IOColor& ioColor) {
		str = str + "\033[" + std::to_string(ioColor.code) + "m";
		return str;
	}

} // namespace DFNS {
