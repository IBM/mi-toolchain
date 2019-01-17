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
 * \file ConsoleOutput.hpp
 * \brief Contains definition of a logger output class responsible for writing (colour) logs onto the console output.
 * \author tkornuta
 * \date Dec 1, 2015
 */

#ifndef SRC_CONFIGURATION_CONSOLEOUTPUT_HPP_
#define SRC_CONFIGURATION_CONSOLEOUTPUT_HPP_

#include <logger/LoggerOutput.hpp>

#include <string>
#include <cstdio>
#include <sstream>

namespace mic {
namespace logger {

#include <iostream>

#if defined(WIN32)
#	define WIN32_LEAN_AND_MEAN
#	include <windows.h>
#endif

/*!
 * Set console font color to blue.
 */
inline std::ostream& blue(std::ostream &s)
{
#if defined(WIN32)
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE);
#else
	s << "\033[34m";
#endif

	return s;
}

/*!
 * Set console font color to green.
 */
inline std::ostream& green(std::ostream &s)
{
	#if defined(WIN32)
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN);
#else
	s << "\033[32m";
#endif

    return s;
}

/*!
 * Set console font color to red.
 */
inline std::ostream& red(std::ostream &s)
{
#if defined(WIN32)
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, FOREGROUND_RED);
#else
	s << "\033[31m";
#endif

	return s;
}

/*!
 * Set console font color to white.
 */
inline std::ostream& white(std::ostream &s)
{
#if defined(WIN32)
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
#else
	s << "\033[37m";
#endif

    return s;
}

/*!
 * Set console font color to yellow.
 */
inline std::ostream& yellow(std::ostream &s)
{
#if defined(WIN32)
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, FOREGROUND_RED|FOREGROUND_GREEN);
#else
	s << "\033[33m";
#endif

    return s;
}

/*!
 * Set console font color to magenta.
 */
inline std::ostream& magenta(std::ostream &s)
{
#if defined(WIN32)
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, FOREGROUND_RED|FOREGROUND_BLUE);
#else
	s << "\033[35m";
#endif

    return s;
}

/*!
 * Set console font color to cyan.
 */
inline std::ostream& cyan(std::ostream &s)
{
#if defined(WIN32)
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN|FOREGROUND_BLUE);
#else
	s << "\033[36m";
#endif

    return s;
}

/*!
 * Reset console colors (ie. font color white, background color black).
 */
inline std::ostream& reset(std::ostream &s)
{
	#if defined(WIN32)
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
#else
	s << "\033[00m";
#endif

    return s;
}

/*!
 * Intense console font color.
 */
inline std::ostream& intense(std::ostream &s)
{
#if defined(WIN32)
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

	if (! GetConsoleScreenBufferInfo(hStdout, &csbiInfo))
		return s;

	SetConsoleTextAttribute(hStdout, csbiInfo.wAttributes | FOREGROUND_INTENSITY);
#else
	s << "\033[1m";
#endif

	return s;
}

/*!
 * \brief Class responsible for printing logs on console.
 */
class ConsoleOutput : public LoggerOutput {
public:
	/*!
	 * Constructor. Sets default severity level (LINFO as default).
	 * @param sev Default output severity level.
	 */
	ConsoleOutput(Severity_t sev = LINFO) :
		LoggerOutput(sev)
	{

	}

	/*!
	 * Virtual destructor. Empty.
	 */
	virtual ~ConsoleOutput(){}


	/*!
	 * Prints message on console, with colours.
	 * @param msg Message to be printed.
	 * @param sev Severity level.
	 * @param file File that called the log function.
	 * @param line Line in which log function was called.
	 */
	void print(const std::string & msg, Severity_t sev, const std::string & file, int line) const {
		switch (sev) {
		case Trace:
			std::cout << cyan << sev2str(sev) << reset << " in " << file << " [" << cyan << line << reset << "]";
			break;
		case Debug:
			std::cout << cyan << intense << sev2str(sev) << reset << " in " << file << " [" << cyan << intense << line << reset << "]";
			break;
		case Notice:
			std::cout << sev2str(sev) << reset;
			break;
		case Info:
			std::cout << green << sev2str(sev) << reset;
			break;
		case Status:
			std::cout << green << intense << sev2str(sev) << reset;
			break;
		case Warning:
			std::cout << yellow << sev2str(sev) << reset;
			break;
		case Error:
			std::cout << red << sev2str(sev) << reset;
			break;
		case Fatal:
			std::cout << red << intense << sev2str(sev) << reset;
			break;
		}

		std::cout << ": " << msg << std::endl;
	}
};


} /* namespace logger */
} /* namespace mic */


#endif /* SRC_CONFIGURATION_CONSOLEOUTPUT_HPP_ */
