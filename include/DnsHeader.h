/**
 * @file DnsHeader.h
 * @version 1.0
 * @author Nikolay Trifonov
 *
 * @brief The file represents the declaration of the DNS header.
 */

#ifndef DNS_HEADER_H
#define DNS_HEADER_H

#include <iostream>
#include <vector>
#include <string.h>
#include <stdint.h>
using namespace std;

namespace DFNS {

	// TYPES
	/**
	 * Structure defines DNS header.
	 */
	struct DnsHdrStruct {
		unsigned short transId;

		unsigned char qrFlag		: 1; // query or a response
		unsigned char opCode		: 4;
		unsigned char dnsFlagAa		: 1;
		unsigned char dnsFlagTc 	: 1;
		unsigned char dnsFlagRd 	: 1;

		unsigned char dnsFlagRa 	: 1;
		unsigned char dnsFlagZ 		: 1;
		unsigned char dnsFlagAd 	: 1;
		unsigned char dnsFlagCd 	: 1;
		unsigned char dnsFlagRCode 	: 4;

		unsigned short countOfQueries;
		unsigned short countOfAnswers;
		unsigned short countOfAuthorities;
		unsigned short countOfResourcies;
	};

	/**
	 * Type for DNS header.
	 */
	typedef struct DnsHdrStruct DnsHdrStruct;

	/**
	 * Class declares functionality that allows to retrieve transaction ID.
	 */
	class DnsHeader {

		public:

			// MEMBERS
			/**
			 * Static member that defines header size of DNS message.
			 */
			static const int DNS_HDR_SIZE = 12;

			// CONSTRUCTORS
			/**
		     * Constructor that sets DNS payload.
		     *
		     * @param dnsPayload Stores DNS message.
		     */
			DnsHeader(vector<char>& dnsPayload);

			// DESTRUCTOR
			/**
			 * Deallocates an object.
			 */
			~DnsHeader();

			// OTHER METHODS
			/**
			 * Retrieves transaction ID from DNS payload.
			 */
			int getTransId();

		private:

			// MEMBERS
			/**
			 * Buffer containing DNS payload.
			 */
			vector<char> hdrBuf;

	}; // class DnsHeader

} // namespace DFNS

#endif
