/**
 * @file EndPoint.cpp
 * @version 1.0
 * @author Nikolay Trifonov
 *
 * @brief The file represents the implementation of the end point containing IP and port.
 */

#include "../../include/EndPoint.h"

namespace DFNS {

	// CONSTRUCTORS
	EndPoint::EndPoint() : ip(), port(0) {
	}

	EndPoint::EndPoint(string ip, int port) : ip(ip), port(port) {
	}

	// DESTRUCTOR
	EndPoint::~EndPoint() {
	}

	// GETTERS / SETTERS
	string EndPoint::getIp() {
		return this->ip;
	}

	int EndPoint::getPort() {
		return this->port;
	}

	void EndPoint::setIp(string& ip) {
		this->ip = ip;
	}

	void EndPoint::setPort(int port) {
		this->port = port;
	}

} // namespace DFNS {
