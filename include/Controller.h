/**
 * @file Controller.h
 * @version 1.0
 * @author Nikolay Trifonov
 *
 * @brief The file represents the declaration of the application's controller.
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <vector>
#include <map>
#include <string.h>
using namespace std;

#include "../include/Model.h"
#include "../include/NetComponent.h"
#include "../include/EndPoint.h"
#include "../include/Log.h"

namespace DFNS {

	/**
	 * Class declares logic of DNS forwarder.
	 */
	class Controller {

		public:

			// CONSTRUCTORS
			/**
			 * Default constructor.
			 */
			Controller();

			// DESTRUCTOR
			/**
		     * Destructor that deallocates net component and all end points in the map.
		     */
			~Controller();

			// OTHER METHODS
			/**
		     * Allocate and initialize net component.
		     *
		     * @param logLvl Log level of type Log::LogLvl.
			 * @param upstreamDnsSrvIp IP address of the upstream DNS server.
			 * @param upstreamDnsSrvPort Port number of the upstream DNS server.
		     * @return bool True, if success. False, if error occurs.
		     */
			bool init(Log::LogLvl logLvl,
					  string upstreamDnsSrvIp,
					  int upstreamDnsSrvPort);

			/**
		     * Run controller of DNS forwarder.
		     *
		     * 1. Receives request from client.
		     * 2. Forwards request to DNS server.
		     * 3. Receives reply from DNS server.
		     * 4. Forwards reply to DNS client.
		     *
		     * @return bool True, if success. False, if error occurs.
		     */
			bool run();

		private:

			// MEMBERS
			/**
			 * Pointer to model that stores application's data.
			 */
			Model* model;

			/**
			 * Pointer to NetComponent's object. It is responsible for net communication with
			 * clients and server.
			 */
			NetComponent* netComponent;

	}; // class Controller

} // namespace DFNS

#endif
