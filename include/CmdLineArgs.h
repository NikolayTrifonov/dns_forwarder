/**
 * @file CmdLineArgs.h
 * @version 1.0
 * @author Nikolay Trifonov
 *
 * @brief The file represents the declaration of the command-line arguments' parser.
 */

#ifndef CMD_LINE_ARGS_H
#define CMD_LINE_ARGS_H

#include <iostream>
#include <string.h>
using namespace std;

#include "../include/Log.h"

namespace DFNS {

	/**
	 * Class parses command-line arguments: help message, log's level, IP and port of upstream DNS
	 * server.
	 */
	class CmdLineArgs {		// specify thrown exceptions

		public:

			// CONSTRUCTORS
			/**
			 * Constructor that creates log's help message, initializes log's level, DNS server's
			 * IP and port.
			 */
			CmdLineArgs();

			// DESTRUCTOR
			/**
		     * Destructor deallocates an object.
		     */
			~CmdLineArgs();

			// GETTERS / SETTERS
			/**
		     * Getter method for logLvl member.
		     *
		     * @return Log::LogLvl Log level of the application.
		     */
			Log::LogLvl getLogLvl();

			/**
		     * Getter method for upstreamDnsSrvIp member.
		     *
		     * @return string IP address of upstream DNS server using dot-notation.
		     */
			string getUpstreamDnsSrvIp();

			/**
		     * Getter method for upstreamDnsPort member.
		     *
		     * @return int Port number of upstream DNS server.
		     */
			int getUpstreamDnsPort();

			// OTHER METHODS
			/**
		     * Parse command-line arguments.
		     *
		     * @param argc Number of command-line arguments.
		     * @param argv Array of command-line arguments.
		     * @return void
		     */
			void parse(int argc, char* argv[]);

		private:

			/**
			 * Help message for application's executable.
			 */
			string hlpMsg;

			/**
			 * Verbose or non-verbose log's level.
			 */
			Log::LogLvl logLvl;

			/**
			 * IP address of upstream DNS server.
			 */
			string upstreamDnsSrvIp;

			/**
			 * Port number of upstream DNS server.
			 */
			int upstreamDnsPort;

	}; // class CmdLineArgs

} // namespace DFNS

#endif
