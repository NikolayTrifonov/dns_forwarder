/**
 * @file NetComponent.h
 * @version 1.0
 * @author Nikolay Trifonov
 *
 * @brief The file represents the declaration of the application's network communication.
 */

#ifndef NET_COMPONENT_H
#define NET_COMPONENT_H

#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

namespace DFNS {

	/**
	 * Max size of UDP datagram.
	 */
	static const int UDP_DG_MAX_SIZE = 512;

	/**
	 * Class declares network functionality for DNS forwarder.
	 */
	class NetComponent {

		public:

			// CONSTRUCTORS
			/**
			 * Default constructor.
			 */
			NetComponent();

			// DESTRUCTOR
			/**
			 * Destructor.
			 */
			~NetComponent();

			// OTHER METHODS
			/**
			 * Initialize NetComponent of DNS forwarder.
			 *
		     * 1. Create socket for DNS forwarder - client communication.
		     * 2. Create socket for DNS forwarder - server communication.
		     * 3. Bind socket for DNS forwarder - client communication.
		     *
			 * @param dfSrvIp IP address of DNS forwarder's server.
			 * @param dfSrvPort Port number of DNS forwarder's server.
		     * @return bool True, if success. False, if error occurs.
		     */
			bool init(string dfSrvIp, int dfSrvPort);

			/**
			 * Receive a message from a client.
			 *
			 * Receive a message from a client, store it in msgBuf.
			 * Return srcIp and srcPort. Return numOfRcvdBytes.
			 *
			 * @param srcIp Reference to the string containing source IP address
			 * 				using string dot notation.
			 * @param srcPort Reference to destination port, integer value.
			 * @param msgBuf Reference to vector's buffer containing a message.
			 * @param numOfRcvdBytes Reference to the parameter containing
			 * 						 the number of received bytes.
			 * @return bool True, if success. False, if error occurs.
			 */
			bool recvFromCli(string& srcIp,
							 int& srcPort,
							 vector<char>& msgBuf,
							 int& numOfRcvdBytes);

			/**
			 * Receive a message from a server.
			 *
			 * Receive a message from a server, store it in msgBuf.
			 * Return srcIp and srcPort. Return numOfRcvdBytes.
			 *
			 * @param srcIp Reference to the string containing source IP address
			 * 				using string dot notation.
			 * @param srcPort Reference to destination port, integer value.
			 * @param msgBuf Reference to vector's buffer containing a message.
			 * @param numOfRcvdBytes Reference to the parameter containing
			 * 						 the number of received bytes.
			 * @return bool True, if success. False, if error occurs.
			 */
			bool recvFromSrv(string& srcIp,
							 int& srcPort,
							 vector<char>& msgBuf,
							 int& numOfRcvdBytes);

			/**
			 * Send a message to a server.
			 *
			 * Send msgBuf's payload using destIp and destPort to a server.
			 * Return number of sent bytes in numOfSentBytes.
			 *
			 * @param destIp Reference to the string containing destination IP address
			 * 				 using string dot notation.
			 * @param destPort Destination port, integer value.
			 * @param msgBuf Reference to vector's buffer containing a message.
			 * @param numOfSentBytes Reference to the parameter containing
			 * 						 the number of sent bytes.
			 * @return bool True, if success. False, if error occurs.
			 */
			bool sendToSrv(const string& destIp,
						   const int destPort,
						   const vector<char>& msgBuf,
						   int& numOfSentBytes);

			/**
			 * Send a message to a client.
			 *
			 * Send msgBuf's payload using destIp and destPort to a client.
			 * Return number of sent bytes in numOfSentBytes.
			 *
			 * @param destIp Reference to the string containing destination IP address
			 * 				 using string dot notation.
			 * @param destPort Destination port, integer value.
			 * @param msgBuf Reference to vector's buffer containing a message.
			 * @param numOfSentBytes Reference to the parameter containing
			 * 						 the number of sent bytes.
			 * @return bool True, if success. False, if error occurs.
			 */
			bool sendToCli(const string& destIp,
						   const int destPort,
						   const vector<char>& msgBuf,
						   int& numOfSentBytes);

		private:

			// MEMBERS
			/**
			 * The file descriptor of the socket with binding for communication
			 * between DNS forwarder and client.
			 */
			int socketForwarderAndCli;

			/**
			 * The file descriptor of the socket with no binding for communication
			 * between DNS forwarder and server.
			 */
			int socketForwarderAndSrv;

			// OTHER METHODS
			/**
			 * Receive a message from a socket.
			 *
			 * Receive a message from a socket, store it in msgBuf.
			 * Return srcIp and srcPort. Return numOfRcvdBytes.
			 *
			 * @param socket The file descriptor of the socket.
			 * @param srcIp Reference to the string containing source IP address
			 * 				 using string dot notation.
			 * @param srcPort Reference to destination port, integer value.
			 * @param msgBuf Reference to vector's buffer containing a message.
			 * @param numOfRcvdBytes Reference to the parameter containing
			 * 						 the number of received bytes.
			 * @return bool True, if success. False, if error occurs.
			 */
			bool recvFrom(int socket, string& srcIp, int& srcPort,
						  vector<char>& msgBuf, int& numOfRcvdBytes);

			/**
			 * Send a message on a socket.
			 *
			 * Send msgBuf's payload using destIp and destPort over socket.
			 * Return number of sent bytes in numOfSentBytes.
			 *
			 * @param socket The file descriptor of the sending socket.
			 * @param destIp Reference to the string containing destination IP address
			 * 				 using string dot notation.
			 * @param destPort Destination port, integer value.
			 * @param msgBuf Reference to vector's buffer containing a message.
			 * @param numOfSentBytes Reference to the parameter containing
			 * 						 the number of sent bytes.
			 * @return bool True, if success. False, if error occurs.
			 */
			bool sendTo(int socket, const string& destIp, const int destPort,
					    const vector<char>& msgBuf, int& numOfSentBytes);

	}; // class NetComponent

} // namespace DFNS

#endif
