/**
 * @file NetComponent.cpp
 * @version 1.0
 * @author Nikolay Trifonov
 *
 * @brief The file represents the implementation of the application's network communication.
 */

#include <netinet/in.h>
#include <arpa/inet.h>

#include "../../include/NetComponent.h"
#include "../../include/Log.h"

namespace DFNS {

	// CONSTRUCTORS
	NetComponent::NetComponent() :	socketForwarderAndCli(-1),
									socketForwarderAndSrv(-1) {
	}

	// DESTRUCTOR
	NetComponent::~NetComponent() {
	}

	// public: OTHER METHODS
	bool NetComponent::init(string dfSrvIp, int dfSrvPort) {
		bool statusOk = true;

		// 1. Create socket for DNS forwarder - client communication.
		this->socketForwarderAndCli = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (this->socketForwarderAndCli == -1) {
			statusOk = false;
			Log::printVars(Log::MSG_TYPE_ERR, "Failed to call socket(). %s, errno = %d.",
						   strerror(errno), errno);
			return statusOk;
		}

		// 2. Create socket for DNS forwarder - server communication.
		this->socketForwarderAndSrv = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (this->socketForwarderAndSrv == -1) {
			statusOk = false;
			Log::printVars(Log::MSG_TYPE_ERR, "Failed to call socket(). %s, errno = %d.",
						   strerror(errno), errno);
			return statusOk;
		}

		// 3. Bind socket for DNS forwarder - client communication.
		struct sockaddr_in dfSrvAddr;
		memset(&dfSrvAddr, 0, sizeof(dfSrvAddr));
		dfSrvAddr.sin_family 		= AF_INET;
		dfSrvAddr.sin_addr.s_addr	= inet_addr(dfSrvIp.data());
		dfSrvAddr.sin_port			= htons(dfSrvPort);

		int retVal = bind(this->socketForwarderAndCli,
						  (struct sockaddr *) &dfSrvAddr,
						  sizeof(struct sockaddr_in));
		if (retVal == -1) {
			statusOk = false;
			Log::printVars(Log::MSG_TYPE_ERR, "Failed to call bind(). %s, errno = %d.",
						   strerror(errno), errno);
			return statusOk;
		}

		return statusOk;
	}

	bool NetComponent::recvFromCli(string& srcIp, int& srcPort, vector<char>& msgBuf,
								   int& numOfRcvdBytes) {
		bool statusOk = true;

		statusOk = recvFrom(this->socketForwarderAndCli, srcIp, srcPort,
							msgBuf, numOfRcvdBytes);
		if (!statusOk) {
			Log::printMsg(Log::MSG_TYPE_ERR, "Failed to call recvFrom().");
		}

		return statusOk;
	}

	bool NetComponent::recvFromSrv(string& srcIp, int& srcPort, vector<char>& msgBuf,
								   int& numOfRcvdBytes) {
		bool statusOk = true;

		statusOk = recvFrom(this->socketForwarderAndSrv, srcIp, srcPort,
							msgBuf, numOfRcvdBytes);
		if (!statusOk) {
			Log::printMsg(Log::MSG_TYPE_ERR, "Failed to call recvFrom().");
		}

		return statusOk;
	}

	bool NetComponent::sendToSrv(const string& destIp,
								 const int destPort,
								 const vector<char>& msgBuf,
								 int& numOfSentBytes) {
		bool statusOk = true;

		statusOk = sendTo(this->socketForwarderAndSrv, destIp, destPort,
						  msgBuf, numOfSentBytes);
		if (!statusOk) {
			Log::printMsg(Log::MSG_TYPE_ERR, "Failed to call sendTo().");
		}

		return statusOk;
	}

	bool NetComponent::sendToCli(const string& destIp,
								 const int destPort,
								 const vector<char>& msgBuf,
								 int& numOfSentBytes) {
		bool statusOk = true;

		statusOk = sendTo(this->socketForwarderAndCli, destIp, destPort,
					  	  msgBuf, numOfSentBytes);
		if (!statusOk) {
			Log::printMsg(Log::MSG_TYPE_ERR, "Failed to call sendTo().");
		}

		return statusOk;
	}

	// private: OTHER METHODS
	bool NetComponent::recvFrom(int socket,
							    string& srcIp,
								int& srcPort,
								vector<char>& msgBuf,
								int& numOfRcvdBytes) {
		bool statusOk = true;
		int addrLength = sizeof(struct sockaddr_in);
		char srcIpCharBuf[INET_ADDRSTRLEN];
		struct sockaddr_in srcAddr;

		memset(&srcAddr, 0, sizeof(srcAddr));

		msgBuf.resize(UDP_DG_MAX_SIZE);
		numOfRcvdBytes = recvfrom(socket,
								  (char *) msgBuf.data(),
								  UDP_DG_MAX_SIZE,
								  MSG_WAITALL,
								  (struct sockaddr *) &srcAddr,
								  (socklen_t *) &addrLength);
		if (numOfRcvdBytes == -1) {
			statusOk = false;
			Log::printVars(Log::MSG_TYPE_ERR, "Failed to call recvfrom(). %s, errno = %d.",
						   strerror(errno), errno);
			return statusOk;
		}

		msgBuf.resize(numOfRcvdBytes);

		inet_ntop(AF_INET, &(srcAddr.sin_addr), srcIpCharBuf, sizeof(srcIpCharBuf));
		srcIp = string(srcIpCharBuf);

		srcPort = htons(srcAddr.sin_port);

		return statusOk;
	}


	bool NetComponent::sendTo(int socket,
							  const string& destIp,
							  const int destPort,
							  const vector<char>& msgBuf,
							  int& numOfSentBytes) {
		bool statusOk = true;
		struct sockaddr_in destAddr;

		memset(&destAddr, 0, sizeof(destAddr));

		destAddr.sin_family    	 = AF_INET;
		destAddr.sin_addr.s_addr = inet_addr(destIp.data());
		destAddr.sin_port 		 = htons(destPort);

		numOfSentBytes = sendto(socket,
								msgBuf.data(),
								msgBuf.size(),
								MSG_CONFIRM,
								(const struct sockaddr *) &destAddr,
								sizeof(struct sockaddr_in));
		if (numOfSentBytes == -1) {
			statusOk = false;
			Log::printVars(Log::MSG_TYPE_ERR, "Failed to call sendto(). %s, errno = %d.",
						   strerror(errno), errno);
		}

		return statusOk;
	}

} // namespace DFNS {
