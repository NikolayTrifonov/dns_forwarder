/**
 * @file Controller.cpp
 * @version 1.0
 * @author Nikolay Trifonov
 *
 * @brief The file represents the implementation of the application's controller.
 */

#include "../../include/Controller.h"
#include "../../include/Model.h"
#include "../../include/NetComponent.h"
#include "../../include/DnsHeader.h"
#include "../../include/Log.h"

namespace DFNS {

	// CONSTRUCTORS
	Controller::Controller() : model(NULL), netComponent(NULL) {
	}

	// DESTRUCTOR
	Controller::~Controller() {
		delete this->model;
		delete this->netComponent;
	}

	// OTHER METHODS
	bool Controller::init(Log::LogLvl logLvl, string upstreamDnsSrvIp, int upstreamDnsSrvPort) {
		bool statusOk = true;

		this->model = new(std::nothrow) Model();
		if (this->model == NULL) {
			statusOk = false;
			Log::printMsg(Log::MSG_TYPE_ERR, "Failed to allocate model object.");
			return statusOk;
		}

		statusOk = this->model->init(logLvl, upstreamDnsSrvIp, upstreamDnsSrvPort);
		if (!statusOk) {
			Log::printMsg(Log::MSG_TYPE_ERR, "Failed to initialize model object.");
			return statusOk;
		}

		this->netComponent = new(std::nothrow) NetComponent();
		if (this->netComponent == NULL) {
			statusOk = false;
			Log::printMsg(Log::MSG_TYPE_ERR, "Failed to allocate netComponent object.");
			return statusOk;
		}

		statusOk = this->netComponent->init(this->model->getDfSrvIp(), this->model->getDfSrvPort());
		if (!statusOk) {
			Log::printMsg(Log::MSG_TYPE_ERR, "Failed to initialize netComponent object.");
		}

		return statusOk;
	}

	bool Controller::run() {
		bool statusOk = true;
		int transId = 0;
		int numOfSentBytes = 0;
		int numOfRcvdBytes = 0;

		string srcIp;
		int srcPort = 0;
		vector<char> rcvMsgBuf;

		string destIp;
		int destPort = 0;
		vector<char> sndMsgBuf;

		while (true) {

			// 1. RECEIVE REQUEST FROM CLIENT
			cout << endl;
			Log::printVars(Log::MSG_TYPE_INF, "[transID]-->Receive DNS datagram from client.");
			statusOk = this->netComponent->recvFromCli(srcIp, srcPort, rcvMsgBuf, numOfRcvdBytes);
			if (!statusOk) {
				Log::printMsg(Log::MSG_TYPE_ERR, "Failed to receive DNS datagram from client.");
				continue;
			}
			// Get transaction id.
			DnsHeader cliHdr(rcvMsgBuf);
			transId = cliHdr.getTransId();
			Log::printVars(Log::MSG_TYPE_DBG, "[ %d ]-->Transaction ID: %d.", transId, transId);
			Log::printVars(Log::MSG_TYPE_DBG, "[ %d ]-->Received bytes: %d.", transId, numOfRcvdBytes);

			// Check if key transId exists in the map.
			if (this->model->isTransIdInMap(transId)) {
				// Duplicated transaction id is found: transId, ignore request.
				Log::printVars(Log::MSG_TYPE_WRN,
							   "[ %d ]-->Duplicated transaction ID found: %d. Ignore request.",
							   transId, transId);
				continue;
			} else {
				// Store client end point in transaction-id map.
				this->model->addEndPoint(transId, srcIp, srcPort);
				//continue; /***** Uncomment in order to test duplicated transaction IDs. *****/
			}

			// 2. FORWARD REQUEST TO DNS SERVER
			sndMsgBuf = rcvMsgBuf;
			numOfSentBytes = 0;
			Log::printVars(Log::MSG_TYPE_INF, "[ %d ]<--Forward request to DNS server.", transId);
			statusOk = netComponent->sendToSrv(this->model->getDnsSrvIp(),
											   this->model->getDnsSrvPort(),
											   sndMsgBuf,
											   numOfSentBytes);
			// Error conditions don't require sending error packet to client.
			if (!statusOk) {
				Log::printMsg(Log::MSG_TYPE_ERR, "Failed to forward request to DNS server.");
				continue;
			}
			Log::printVars(Log::MSG_TYPE_DBG, "[ %d ]<--Sent bytes: %d.", transId, numOfSentBytes);

			// 3. RECEIVE REPLY FROM DNS SERVER
			Log::printVars(Log::MSG_TYPE_INF, "[transID]-->Receive DNS datagram from server.");
			statusOk = netComponent->recvFromSrv(srcIp, srcPort, rcvMsgBuf, numOfRcvdBytes);
			// Error conditions don't require sending error packet to client.
			if (!statusOk) {
				Log::printMsg(Log::MSG_TYPE_ERR, "Failed to receive DNS datagram from server.");
				continue;
			}
			// Get transaction ID.
			DnsHeader srvHdr(rcvMsgBuf);
			transId = srvHdr.getTransId();
			Log::printVars(Log::MSG_TYPE_DBG, "[ %d ]-->Transaction ID: %d", transId, transId);
			Log::printVars(Log::MSG_TYPE_DBG, "[ %d ]-->Received bytes: %d.", transId, numOfRcvdBytes);

			// Find client's end point in transaction-id map.
			EndPoint endPoint = this->model->getEndPoint(transId);
			destIp = endPoint.getIp();
			destPort = endPoint.getPort();
			if ((destIp.empty()) or (destPort == 0)) {
				statusOk = false;
				Log::printVars(Log::MSG_TYPE_ERR, "Failed to find client's end point in "
							   "transaction id map: ip = %s, port = %d.", destIp.data(), destPort);
			}
			// Error conditions don't require sending error packet to client.
			if (!statusOk) {
				continue;
			}

			// 4. FORWARD REPLY TO DNS CLIENT
			numOfSentBytes = 0;
			sndMsgBuf = rcvMsgBuf;
			Log::printVars(Log::MSG_TYPE_INF, "[ %d ]<--Forward reply to DNS client.", transId);
			statusOk = this->netComponent->sendToCli(destIp, destPort, sndMsgBuf, numOfSentBytes);
			if (!statusOk) {
				Log::printMsg(Log::MSG_TYPE_ERR, "Failed to forward reply to DNS client.");
				continue;
			}
			Log::printVars(Log::MSG_TYPE_DBG, "[ %d ]<--Sent bytes: %d.", transId, numOfSentBytes);

		} // while (true) {

		return statusOk;
	}

} // namespace DFNS {
