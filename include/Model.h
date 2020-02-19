/**
 * @file Model.h
 * @version 1.0
 * @author Nikolay Trifonov
 *
 * @brief The file represents the declaration of the model containing application's data.
 */

#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <map>
#include <string.h>
using namespace std;

#include "../include/EndPoint.h"
#include "../include/Log.h"

namespace DFNS {

	/**
	 * Class stores IP-port pair.
	 */
	class Model {

		public:

			// CONSTANTS
			/**
			 * Server IP of listen endpoint for DNS forwarder.
			 */
			static const char* DF_SRV_IP;

			/**
			 * Server port of listen endpoint for DNS forwarder.
			 */
			static const int DF_SRV_PORT;

			// CONSTRUCTORS
			/**
			 * Default constructor.
			 */
			Model();

			// DESTRUCTOR
			/**
			 * Destructor that deallocates an object.
			 */
			~Model();

			// GETTERS / SETTERS
			/**
			 * Getter for dfSrvIp member.
			 *
			 * @return string IP address in dot-notation.
			 */
			string getDfSrvIp();

			/**
			 * Getter for dfSrvPort member.
			 *
			 * @return int Port number.
			 */
			int getDfSrvPort();

			/**
			 * Getter for dnsSrvIp member.
			 *
			 * @return string IP address in dot-notation.
			 */
			string getDnsSrvIp();

			/**
			 * Getter for dnsSrvPort member.
			 *
			 * @return int Port number.
			 */
			int getDnsSrvPort();

			// OTHER METHODS
			/**
		     * Sets log level. Allocates and initializes controller.
		     *
		     * @return bool True, if success. False, if error occurs.
		     */
			bool init(Log::LogLvl logLvl, string upstreamDnsSrvIp, int upstreamDnsSrvPort);

			/**
			 * Check if transId is in the map.
			 *
			 * @param transId Transaction ID integer number.
			 * @return true, if found, false, otherwise.
			 */
			bool isTransIdInMap(int transId);

			/**
			 * Add ip-port end point to the map.
			 *
			 * @param transId Transaction ID integer number.
			 * @param ip Reference to string containing IP number in dot notation.
			 * @param port Port number, integer value.
			 * @return void
			 */
			void addEndPoint(int transId, string& ip, int port);

			/**
			 * Find and return EndPoint using transId number.
			 *
			 * @param  transId Transaction ID integer number.
			 * @return EndPoint object. If not found, the object contains empty IP string and zero
			 * 		   port.
			 */
			EndPoint getEndPoint(int transId);

		private:

			// MEMBERS
			/**
			 * Server IP of DNS Forwarder, listen endpoint is hardcoded to 127.0.0.1:1917.
			 */
			string dfSrvIp;

			/**
			 * Server port of DNS Forwarder, listen endpoint is hardcoded to 127.0.0.1:1917.
			 */
			int dfSrvPort;

			/**
			 * IP of upstream DNS server, from command line arguments.
			 */
			string dnsSrvIp;

			/**
			 * Port of upstream DNS server, from command line arguments.
			 */
			int dnsSrvPort;

			/**
			 * Map of clients' end-points(IP+port). Key - transaction ID. Value - EndPoint object.
			 */
			map<int, EndPoint*> cliTransIdMap;

	}; // class Model

} // namespace DFNS {

#endif
