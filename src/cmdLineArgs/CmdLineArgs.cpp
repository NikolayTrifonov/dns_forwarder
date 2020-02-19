/**
 * @file CmdLineArgs.cpp
 * @version 1.0
 * @author Nikolay Trifonov
 *
 * @brief The file represents the implementation of the command-line arguments' parser.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "../../include/CmdLineArgs.h"
#include "../../include/Log.h"
#include "../../include/IOColor.h"
#include "../../include/Common.h"

namespace DFNS {

	// CONSTRUCTORS
	CmdLineArgs::CmdLineArgs() : hlpMsg(""),
								 logLvl(Log::LOG_LVL_NORMAL),
								 upstreamDnsSrvIp(),
								 upstreamDnsPort(0) {
		string copyrightName  = "Copyright";
		string copyrightValue = "© Nikolay Trifonov";
		string description = "Description: The application listens to the fixed UDP port 1917 and sends "
							 "incoming messages\n             to an upstream server.";
		string usage = "Usage: dns_forwarder [-h] [-v] ip port\n";
		string options = "Options:\n"
						 "-h Print help message.\n"
						 "-v Enable verbose mode.\n"
						 "ip IP address of upstream DNS server.\n"
						 "port Port number of upstream DNS server.";
		string client = "Client:\n"
						"dig @127.0.0.1 -p 1917 -4 hs.fi";

		IOColor ioColorYellow(IOColor::FG_CODE_BRIGHT_YELLOW);
		IOColor ioColorBlue(IOColor::FG_CODE_BRIGHT_BLUE);
		IOColor ioColorReset(IOColor::FG_CODE_RESET_NORMAL);

		this->hlpMsg = this->hlpMsg + ioColorYellow;
		this->hlpMsg += description;
		this->hlpMsg = this->hlpMsg + ioColorReset;
		this->hlpMsg += "\n";

		this->hlpMsg = this->hlpMsg + ioColorYellow;
		this->hlpMsg += usage;
		this->hlpMsg = this->hlpMsg + ioColorReset;

		this->hlpMsg = this->hlpMsg + ioColorYellow;
		this->hlpMsg += options;
		this->hlpMsg = this->hlpMsg + ioColorReset;

		this->hlpMsg = this->hlpMsg + ioColorYellow;
		this->hlpMsg += "\n";
		this->hlpMsg += "\n";
		this->hlpMsg += client;
		this->hlpMsg = this->hlpMsg + ioColorReset;
	}

	// DESTRUCTOR
	CmdLineArgs::~CmdLineArgs() {
	}

	// GETTERS / SETTERS
	Log::LogLvl CmdLineArgs::getLogLvl() {
		return this->logLvl;
	}

	string CmdLineArgs::getUpstreamDnsSrvIp() {
		return this->upstreamDnsSrvIp;
	}

	int CmdLineArgs::getUpstreamDnsPort() {
		return this->upstreamDnsPort;
	}

	// OTHER METHODS
	void CmdLineArgs::parse(int argc, char* argv[]) {
		int opt = 0;

		while ((opt = getopt(argc, argv, "hv")) != -1) {
			switch (opt) {
				case 'h':
					Log::printMsg(Log::MSG_TYPE_INF, this->hlpMsg);
					exit(APP_EXIT_SUCCESS);
					break;

				case 'v':
					this->logLvl = Log::LOG_LVL_VERBOSE;
					break;

				default:
					Log::printMsg(Log::MSG_TYPE_ERR, "Usage: dns_forwarder [-h] [-v] ip port");
					exit(APP_EXIT_FAILURE);
			}
		}

		if ((this->logLvl == Log::LOG_LVL_NORMAL) and (argc == 3)) {
			this->upstreamDnsSrvIp = argv[1];
			this->upstreamDnsPort = atoi(argv[2]);
		} else if ((this->logLvl == Log::LOG_LVL_VERBOSE) and (argc == 4)) {
			this->upstreamDnsSrvIp = argv[2];
			this->upstreamDnsPort = atoi(argv[3]);
		} else {
			Log::printMsg(Log::MSG_TYPE_ERR, "Usage: dns_forwarder [-h] [-v] ip port");
			exit(APP_EXIT_FAILURE);
		}
	}

} // namespace DFNS {
