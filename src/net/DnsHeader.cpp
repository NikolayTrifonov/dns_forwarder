/**
 * @file DnsHeader.cpp
 * @version 1.0
 * @author Nikolay Trifonov
 *
 * @brief The file represents the implementation of the DNS header.
 */

#include <netinet/in.h>
#include <arpa/inet.h>

#include "../../include/DnsHeader.h"
#include "../../include/Log.h"

namespace DFNS {

	// CONSTRUCTORS
	DnsHeader::DnsHeader(vector<char>& dnsPayload) :
		hdrBuf(dnsPayload.begin(), dnsPayload.begin() + DNS_HDR_SIZE - 1) {
	}

	// DESTRUCTOR
	DnsHeader::~DnsHeader() {
	}

	// OTHER METHODS
	int DnsHeader::getTransId() {
		DnsHdrStruct* hdr = (DnsHdrStruct* ) hdrBuf.data();
		int transId = ntohs(hdr->transId);
		return transId;
	}

} // namespace DFNS {
