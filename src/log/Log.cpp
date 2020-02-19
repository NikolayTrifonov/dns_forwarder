/**
 * @file Log.cpp
 * @version 1.0
 * @author Nikolay Trifonov
 *
 * @brief The file represents the implementation of the application's logging/tracing.
 */

#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

#include "../../include/Log.h"
#include "../../include/IOColor.h"

namespace DFNS {

	// MEMBERS
	int Log::logLvl = Log::LOG_LVL_NORMAL;

	// public: OTHER METHODS
	void Log::printMsg(MsgType msgType,
					   const string& msg,
					   const string& funcName,
					   const string& fileName) {

		if (Log::logLvl == Log::LOG_LVL_NORMAL) {
			Log::printMsg(msgType, msg, false, false, false, funcName, fileName);
		} else {
			Log::printMsg(msgType, msg, true, true, false, funcName, fileName);
		}
	}

	void Log::printMsg(MsgType msgType,
					   const char* msg,
					   const string& funcName,
					   const string& fileName) {
		if (Log::logLvl == Log::LOG_LVL_NORMAL) {
			Log::printMsg(msgType, msg, false, false, false, funcName, fileName);
		} else {
			Log::printMsg(msgType, msg, true, true, false, funcName, fileName);
		}
	}

	void Log::printVars(MsgType msgType, string formatMsg, ...) {
		char buffer[256];
		va_list args;

		va_start(args, formatMsg);
		vsprintf(buffer, formatMsg.data(), args);

		string msg = string(buffer);
		Log::printMsg(msgType, msg);

		va_end(args);
	}

	// private: OTHER METHODS
	void Log::printMsg(MsgType msgType,
					   const string& msg,
					   bool printMsgType,
					   bool printTimeStamp,
					   bool printFuncName,
					   const string& funcName,
					   const string& fileName) {

		string finalMsg = "";
		if (printTimeStamp) {
			finalMsg += Log::getTimeStamp() + " ";
		}

		if (printFuncName) {
			finalMsg = finalMsg + Log::getClassName(fileName) + "::";
			finalMsg = finalMsg + Log::getFuncName(funcName) + ": ";
		}

		switch (msgType) {

			case Log::MSG_TYPE_INF:
				if (printMsgType) {
					finalMsg = "INF: " + finalMsg;
				}
				cout << IOColor(IOColor::FG_CODE_BRIGHT_GREEN) << finalMsg << msg <<
						IOColor(IOColor::FG_CODE_RESET_NORMAL) << endl;
				break;

			case Log::MSG_TYPE_DBG:
				if (printMsgType) {
					finalMsg = "DBG: " + finalMsg;
				}
				cout << IOColor(IOColor::FG_CODE_BRIGHT_CYAN) << finalMsg << msg <<
						IOColor(IOColor::FG_CODE_RESET_NORMAL) << endl;
				break;

			case Log::MSG_TYPE_WRN:
				if (printMsgType) {
					finalMsg = "WRN: " + finalMsg;
				}
				cerr << IOColor(IOColor::FG_CODE_BRIGHT_MAGENTA) << finalMsg << msg <<
						IOColor(IOColor::FG_CODE_RESET_NORMAL) << endl;
				break;

			case Log::MSG_TYPE_ERR:
				if (printMsgType) {
					finalMsg = "ERR: ";
				}
				cerr << IOColor(IOColor::FG_CODE_BRIGHT_RED) << msg <<
						IOColor(IOColor::FG_CODE_RESET_NORMAL) << endl;
				break;

			default:
				Log::printVars(Log::MSG_TYPE_ERR, "Unknow message type.");
				break;
		}
	}

	void Log::printMsg(MsgType msgType,
					   const char* msg,
					   bool printMsgType,
					   bool printTimeStamp,
					   bool printFuncName,
					   const string& funcName,
					   const string& fileName) {
		string msgStr(msg);
		Log::printMsg(msgType, msgStr, printTimeStamp, printMsgType, printFuncName, funcName,
					  fileName);
	}

	string Log::getTimeStamp() {
		time_t numOfSec = time(NULL);
		tm timeStruct = *localtime(&numOfSec);
		ostringstream oss;
		oss << put_time(&timeStruct, "%Y.%m.%d %H:%M:%S");
		string timeStamp(oss.str());

		return timeStamp;
	}

	string Log::getFuncName(const string& funcName) {
		string newFuncName = funcName + "()";
		return newFuncName;
	}

	string Log::getClassName(const string& fileName) {
		int startPosition = fileName.find_last_of('/');
		startPosition += 1;								// correction for '/'
		int endPosition = fileName.find_last_of('.');
		string className = fileName.substr(startPosition, endPosition - startPosition);
		return className;
	}

} // namespace DFNS {
