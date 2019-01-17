/*!
 * Copyright (C) tkornuta, IBM Corporation 2015-2019
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*!
 * \file logger_test.cpp
 * \brief Program for testing logger (with console output).
 * \author tkornuta
 * \date Dec 1, 2015
 */

#include <logger/Log.hpp>
#include <logger/ConsoleOutput.hpp>
#ifdef _WIN32
#include <system_utils/windows_extras.hpp>  
#endif
using namespace mic::logger;


/*!
 * \brief Main program function for testing logger with console output.
 * \author tkornuta
 * @param[in] argc Number of parameters (not used).
 * @param[in] argv List of parameters (not used).
 * @return (not used).
 */
int main(int argc, char* argv[]) {
	// Set console output.
	ConsoleOutput* co = new ConsoleOutput();
	LOGGER->addOutput(co);

	// Set initial logger level.
	int logger_level = 0;
	while(1) {
		std::cout << "\nSetting logger_level to:" << logger_level << std::endl << std::endl;
		// Change logger level.
		co->setLvl((Severity_t)logger_level);

		// Display logs.
		LOG(LTRACE) << "Level 0: trace message ";
		LOG(LDEBUG) << "Level 1: debug message ";
		LOG(LNOTICE) << "Level 2: notice message ";
		LOG(LINFO) << "Level 3: info message ";
		LOG(LSTATUS) << "Level 4: status message ";
		LOG(LWARNING) << "Level 5: warning message ";
		LOG(LERROR) << "Level 6: error message ";
		LOG(LFATAL) << "Level 7: fatal error message ";

		// Change logger level.
		logger_level++;

		// Sleep.
		usleep(1000000);
	}//: while

}//: main
