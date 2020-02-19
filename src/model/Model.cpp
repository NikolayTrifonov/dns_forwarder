/**
 * @file Model.cpp
 * @version 1.0
 * @author Nikolay Trifonov
 *
 * @brief The file represents the implementation of the end point containing IP and port.
 */

#include "../../include/Model.h"

namespace DFNS {
	// CONSTANTS
	const char* Model::DF_SRV_IP = "127.0.0.1";
	const int Model::DF_SRV_PORT = 1917;

	// CONSTRUCTORS
	Model::Model() : dfSrvIp(Model::DF_SRV_IP),
					 dfSrvPort(Model::DF_SRV_PORT),
					 dnsSrvIp(),
					 dnsSrvPort(-1),
					 cliTransIdMap() {
	}

	// DESTRUCTOR
	Model::~Model() {
		// Delete all end points.
		map<int, EndPoint*>::iterator it; // it - input iterator
		for (it = this->cliTransIdMap.begin(); it != this->cliTransIdMap.end(); ++it) {
			delete it->second;
		}
	}

	// GETTERS / SETTERS
	string Model::getDfSrvIp() {
		return this->dfSrvIp;
	}

	int Model::getDfSrvPort() {
		return this->dfSrvPort;
	}

	string Model::getDnsSrvIp() {
		return this->dnsSrvIp;
	}

	int Model::getDnsSrvPort() {
		return this->dnsSrvPort;
	}

	// OTHER METHODS
	bool Model::init(Log::LogLvl logLvl,
					 string upstreamDnsSrvIp,
					 int upstreamDnsSrvPort) {
		bool statusOk = true;

		Log::logLvl = logLvl;
		this->dnsSrvIp = upstreamDnsSrvIp;
		this->dnsSrvPort = upstreamDnsSrvPort;

		return statusOk;
	}

	bool Model::isTransIdInMap(int transId) {
		return (this->cliTransIdMap.count(transId) > 0);
	}

	void Model::addEndPoint(int transId, string& ip, int port) {
		EndPoint* endPoint = new(std::nothrow) EndPoint(ip, port);
		if (endPoint != NULL) {
			this->cliTransIdMap[transId] = endPoint;
		} else {
			Log::printMsg(Log::MSG_TYPE_ERR, "Failed to allocate endPoint.");
		}
	}

	EndPoint Model::getEndPoint(int transId) {
		EndPoint* endPoint = this->cliTransIdMap[transId];
		if (endPoint != NULL) {
			return *endPoint;
		}
		return EndPoint();
	}

} // namespace DFNS {
