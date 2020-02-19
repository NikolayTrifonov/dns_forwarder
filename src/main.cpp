/**
 * @file main.cpp
 * @version 1.0
 * @author Nikolay Trifonov
 *
 * @brief The file represents the declaration of the application's main function.
 *
 * The file contains a global function named main, which starts the program.
 */

#include <iostream>
#include <typeinfo>
#include <time.h>
#include <unistd.h>
#include <cstdio>
#include <chrono>
#include <iomanip>
using namespace std;

#include "../include/CmdLineArgs.h"
#include "../include/DnsForwarder.h"
#include "../include/Log.h"
#include "../include/Common.h"
using namespace DFNS;

/**
 * Global function main, which starts the program.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int MAIN_RETURN_SUCCESS if success, MAIN_RETURN_FAILURE if failure.
 */
int main(int argc, char* argv[]) {
	bool statusOk = true;
	int retVal = 0;

	string welcomingMsg = "DNS Forwarder v.1.0 / © Nikolay Trifonov";
	Log::printMsg(Log::MSG_TYPE_INF, welcomingMsg);

	// 1. Get command-line arguments.
	CmdLineArgs cmdLineArgs;
	cmdLineArgs.parse(argc, argv);

	// 2. Create DNS forwarder.
	DnsForwarder* dnsForwarder = new(std::nothrow) DnsForwarder();
	if (dnsForwarder == NULL) {
		Log::printMsg(Log::MSG_TYPE_ERR, "Failed to allocate dnsForwarder object.");
		return MAIN_RETURN_FAILURE;
	}

	// 3. Initialize DNS forwarder.
	statusOk = dnsForwarder->init(cmdLineArgs.getLogLvl(),
								  cmdLineArgs.getUpstreamDnsSrvIp(),
								  cmdLineArgs.getUpstreamDnsPort());
	if (!statusOk) {
		Log::printMsg(Log::MSG_TYPE_ERR, "Failed to initialize dnsForwarder.");
		return MAIN_RETURN_FAILURE;
	}

	// 4. Run DNS forwarder.
	statusOk = dnsForwarder->run();
	if (!statusOk) {
		Log::printMsg(Log::MSG_TYPE_ERR, "Failed to run dnsForwarder.");
		return MAIN_RETURN_FAILURE;
	}

	// 5. Clean.
	delete dnsForwarder;

	retVal = (statusOk) ? MAIN_RETURN_SUCCESS : MAIN_RETURN_FAILURE;
	return retVal;
}
