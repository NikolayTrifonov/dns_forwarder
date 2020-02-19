/**
 * @file DnsForwarder.cpp
 * @version 1.0
 * @author Nikolay Trifonov
 *
 * @brief The file represents the implementation of the DNS forwarder.
 */

#include "../../include/DnsForwarder.h"
#include "../../include/Controller.h"
#include "../../include/Log.h"

namespace DFNS {

	// CONSTRUCTORS
	DnsForwarder::DnsForwarder() : controller(NULL) {
	}

	// DESTRUCTOR
	DnsForwarder::~DnsForwarder() {
		delete this->controller;
	}

	// OTHER METHODS
	bool DnsForwarder::init(Log::LogLvl logLvl,
							string upstreamDnsSrvIp,
							int upstreamDnsSrvPort) {
		bool statusOk = true;
		this->controller = new(std::nothrow) Controller();
		if (this->controller == NULL) {
			statusOk = false;
			Log::printMsg(Log::MSG_TYPE_ERR, "Failed to allocate controller object.");
			return statusOk;
		}
		statusOk = this->controller->init(logLvl, upstreamDnsSrvIp, upstreamDnsSrvPort);
		if (!statusOk) {
			Log::printMsg(Log::MSG_TYPE_ERR, "Failed to initialize controller.");
		}
		return statusOk;
	}

	bool DnsForwarder::run() {
		bool statusOk = true;
		statusOk = this->controller->run();
		if (!statusOk) {
			statusOk = false;
			Log::printMsg(Log::MSG_TYPE_ERR, "Failed to run controller.");
		}
		return statusOk;
	}

} // namespace DFNS {
