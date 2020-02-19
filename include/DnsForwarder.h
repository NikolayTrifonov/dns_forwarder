/**
 * @file DnsForwarder.h
 * @version 1.0
 * @author Nikolay Trifonov
 *
 * @brief The file represents the declaration of the DNS forwarder.
 *
 * The application listens for UDP port and sends incoming messages to an upstream server.
 * Server’s replies are returned to the corresponding client end-points.
 */

#ifndef DNS_FORWARDER_H
#define DNS_FORWARDER_H

#include "../include/Controller.h"
#include "../include/Log.h"

namespace DFNS {

	/**
	 * Class declares functionality of DNS forwarder.
	 */
	class DnsForwarder {

		public:

			// CONSTRUCTORS
			/**
			 * Default constructor.
		     */
			DnsForwarder();

			// DESTRUCTOR
			/**
		     * Destructor deallocates controller.
		     */
			~DnsForwarder();

			// OTHER METHODS
			/**
		     * Set log level. Allocate and initialize controller.
		     *
		     * @param logLvl Log level of type Log::LogLvl.
			 * @param upstreamDnsSrvIp IP address of the upstream DNS server.
			 * @param upstreamDnsSrvPort Port number of the upstream DNS server.
		     * @return bool True, if success. False, if error occurs.
		     */
			bool init(Log::LogLvl logLvl, string upstreamDnsSrvIp, int upstreamDnsSrvPort);

			/**
		     * Run controller.
		     *
		     * @return bool True, if success. False, if error occurs.
		     */
			bool run();

		private:

			// MEMBERS
			/**
			 * Controller that defines the logic of the application.
			 */
			Controller* controller;

	}; // class DnsForwarder

} // namespace DFNS

#endif
