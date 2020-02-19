/**
 * @file IOColor.h
 * @version 1.0
 * @author Nikolay Trifonov
 *
 * @brief The file represents the declaration of the input-output color's scheme.
 */

#ifndef IO_COLOR_H
#define IO_COLOR_H

#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

namespace DFNS {

/**
 * Class declares color scheme for console.
 */
class IOColor {

		public:

			// TYPES
			/**
			 * Enum type that defines color codes.
			 */
			enum Codes {
				FG_CODE_RESET_NORMAL   = 0,
				FG_CODE_BRIGHT_RED	   = 91,
				FG_CODE_BRIGHT_GREEN   = 92,
				FG_CODE_BRIGHT_YELLOW  = 93,
				FG_CODE_BRIGHT_BLUE	   = 94,
				FG_CODE_BRIGHT_MAGENTA = 95,
				FG_CODE_BRIGHT_CYAN	   = 96
			};

			// CONSTRUCTORS
			/**
			 * Constructor that sets color's code.
			 *
			 * @param code Code number of type Codes.
			 */
			IOColor(Codes code);

			// DESTRUCTOR
			/**
			 * Destructor deallocates an object.
			 */
			~IOColor();

			// OVERLOADED OPERATORS

			/**
			 * Overloaded output stream operator.
			 *
			 * @param os Output stream.
			 * @param ioColor Reference to object that defines color's scheme.
			 * @return Escape sequence that changes the color of the text in console.
			 */
			friend std::ostream& operator<<(std::ostream& os, const IOColor& ioColor);

			/**
			 * Overloaded plus operator.
			 *
			 * @param str String.
			 * @param ioColor Reference to object that defines color's scheme.
			 * @return string String that changes the color of the text in console.
			 */
			friend string& operator+(string& str, IOColor& ioColor);

		private:

			// MEMBERS
			/**
			 * Color code that defines the color's scheme of the object.
			 */
			int code;

	}; // class IOColor

} // namespace DFNS

#endif
