/**
 * @file Log.h
 * @version 1.0
 * @author Nikolay Trifonov
 *
 * @brief The file represents the declaration of the application's logging/tracing.
 */

#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <stdio.h>
#include <stdarg.h>
using namespace std;

namespace DFNS {

	/**
	 * Class declares logging mechanism for the application.
	 */
	class Log {

		public:
			// TYPES
			/**
			 * Enum type of message.
			 */
			enum MsgType {
				MSG_TYPE_INF,
				MSG_TYPE_DBG,
				MSG_TYPE_WRN,
				MSG_TYPE_ERR
			};

			/**
			 * Enum type of log's level.
			 */
			enum LogLvl {
				LOG_LVL_NORMAL,
				LOG_LVL_VERBOSE
			};

			// MEMBERS
			/**
			 * Static member containing log's level.
			 */
			static int logLvl;

			// OTHER METHODS
			/**
			 * Static method for printing various types of messages.
			 *
			 * @param msgType Type of message to be printed.
			 * @param msg Reference to string containing message.
			 * @param funcName Reference to function name with default value
			 * 				   string(__builtin_FUNCTION()).
			 * @param fileName Reference to file name with default value
			 * 				   string(__builtin_FILE()).
			 * @return void
			 */
			static void printMsg(MsgType msgType,
								 const string& msg,
								 const string& funcName = string(__builtin_FUNCTION()),
								 const string& fileName = string(__builtin_FILE()));

			/**
			 * Static method for printing various types of messages.
			 *
			 * @param msgType Type of message to be printed.
			 * @param msg Pointer to char buffer containing message.
			 * @param funcName Reference to function name with default value
			 * 				   string(__builtin_FUNCTION()).
			 * @param fileName Reference to file name with default value
			 * 				   string(__builtin_FILE()).
			 * @return void
			 */
			static void printMsg(MsgType msgType,
								 const char* msg,
								 const string& funcName = string(__builtin_FUNCTION()),
 								 const string& fileName = string(__builtin_FILE()));

			/**
			 * Static method for printing various types of messages.
			 *
			 * @param msgType Type of message to be printed.
			 * @param formatMsg Format string that defines formatted output like in printf().
			 * @param ... Variable number of arguments.
			 * @return void
			 */
			static void printVars(MsgType msgType, string formatMsg, ...);

		private:

			// OTHER METHODS
			/**
			 * Static method for printing various types of messages.
			 *
			 * @param msgType Type of message to be printed.
			 * @param msg Reference to string containing message.
			 * @param printMsgType Boolean flag for printing message type.
			 * @param printTimeStamp Boolean flag for printing time stamp.
			 * @param printFuncName Boolean flag for printing function's name.
			 * @param funcName Reference to function name with default value
			 * 				   string(__builtin_FUNCTION()).
			 * @param fileName Reference to file name with default value
			 * 				   string(__builtin_FILE()).
			 * @return void
			 */
			static void printMsg(MsgType msgType,
								 const string& msg,
							     bool printMsgType,
								 bool printTimeStamp,
							     bool printFuncName,
								 const string& funcName = string(__builtin_FUNCTION()),
								 const string& fileName = string(__builtin_FILE()));

			/**
			 * Static method for printing various types of messages.
			 *
			 * @param msgType Type of message to be printed.
			 * @param msg Pointer to char buffer containing message.
			 * @param printMsgType Boolean flag for printing message type.
			 * @param printTimeStamp Boolean flag for printing time stamp.
			 * @param printFuncName Boolean flag for printing function's name.
			 * @param funcName Reference to function name with default value
			 * 				   string(__builtin_FUNCTION()).
			 * @param fileName Reference to file name with default value
			 * 				   string(__builtin_FILE()).
			 * @return void
			 */
			static void printMsg(MsgType msgType,
								 const char* msg,
							     bool printMsgType,
								 bool printTimeStamp,
								 bool printFuncName,
								 const string& funcName = string(__builtin_FUNCTION()),
 								 const string& fileName = string(__builtin_FILE()));

			/**
			 * Static method that returns the current time-stamp.
			 *
			 * @return string Returns time-stamp using the format "yyyy.mm.dd hh:mm:ss".
			 */
			static string getTimeStamp();

			/**
			 * Static method that returns the name of function.
			 *
			 * @return string Returns the name of function.
			 */
			static string getFuncName(const string& funcName);

			/**
			 * Static method that returns the name of class.
			 *
			 * @return string Returns the name of class.
			 */
			static string getClassName(const string& fileName);

	}; // class Log {

} // namespace DFNS {

#endif
