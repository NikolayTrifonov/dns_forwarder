/**
 * @file EndPoint.h
 * @version 1.0
 * @author Nikolay Trifonov
 *
 * @brief The file represents the declaration of the end point containing IP and port.
 */

#ifndef END_POINT_H
#define END_POINT_H

#include <iostream>
#include <vector>
#include <string.h>
#include <stdint.h>
using namespace std;

namespace DFNS {

	/**
	 * Class stores IP-port pair.
	 */
	class EndPoint {

		public:

			// CONSTRUCTORS
			/**
			 * Default constructor.
			 */
			EndPoint();

			/**
			 * Parameterized constructor.
			 *
			 * @param ip IP address using string dot-notation.
			 * @param port Port number.
			 */
			EndPoint(string ip, int port);

			// DESTRUCTOR
			/**
			 * Destructor that deallocates an object.
			 */
			~EndPoint();

			// GETTERS / SETTERS
			/**
			 * Getter for IP member.
			 *
			 * @return string IP address in dot-notation.
			 */
			string getIp();

			/**
			 * Getter for port member.
			 *
			 * @return int Port number.
			 */
			int getPort();

			/**
			 * Setter for IP member.
			 *
			 * @param ip Reference to string containing IP address in dot-notation.
			 * @return void
			 */
			void setIp(string& ip);

			/**
			 * Setter for port member.
			 *
			 * @param port Port number.
			 * @return void
			 */
			void setPort(int port);

		private:

			// MEMBERS
			/**
			 * IP address in dot-notation.
			 */
			string ip;

			/**
			 * Port number.
			 */
			int port;

	}; // class EndPoint

} // namespace DFNS

#endif
