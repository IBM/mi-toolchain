/*!
 * \file ApplicationState.cpp
 * \brief ApplicationState definition.
 * \author tkornuta
 * \date Nov 16, 2015
 */

#include <application/ApplicationState.hpp>

#include <logger/Log.hpp>

namespace mic {
namespace application {

// Init application instance - as NULL.
boost::atomic<ApplicationState*> ApplicationState::instance_(NULL);

// Initilize mutex.
boost::mutex ApplicationState::instantiation_mutex;

// Initilize internal data synchronization mutex.
boost::mutex ApplicationState::internal_data_synchronization_mutex;

// Initilize external data synchronization mutex.
boost::mutex ApplicationState::external_data_synchronization_mutex;


ApplicationState* ApplicationState::getInstance() {
	// Try to load the instance - first check.
	ApplicationState* tmp = instance_.load(boost::memory_order_consume);
	// If instance does not exist.
	if (!tmp) {
		// Enter critical section.
		boost::mutex::scoped_lock guard(instantiation_mutex);
		// Try to load the instance - second check.
		tmp = instance_.load(boost::memory_order_consume);
		// If still does not exist - create new instance.
		if (!tmp) {
			tmp = new ApplicationState;
			instance_.store(tmp, boost::memory_order_release);
		}//: if
		// Exit critical section.
	}//: if
	// Return instance.
	return tmp;
}


ApplicationState::ApplicationState() : PropertyTree("app_state"),
		pause_mode("pause_mode", false),
		single_step_mode("single_step_mode", false),
		learning_mode("learning_mode", false),
		application_sleep_interval("application_sleep_interval", 1000)
{
	// Register properties - so their values can be overridden (read from the configuration file).
	registerProperty(pause_mode);
	registerProperty(single_step_mode);
	registerProperty(learning_mode);
	registerProperty(application_sleep_interval);

	// Set default application state flags.
	quit_flag = false;

	// Set using gui/cli/visualization to false.
	using_opengl = false;
	using_ncurses = false;
}



// ---------------------- Quit MANAGEMENT.

double ApplicationState::Quit() {
	boost::mutex::scoped_lock lock(internal_data_synchronization_mutex);
	return quit_flag;
}

void ApplicationState::setQuit() {
	boost::mutex::scoped_lock lock(internal_data_synchronization_mutex);
	quit_flag = true;
}

void ApplicationState::resetQuit() {
	boost::mutex::scoped_lock lock(internal_data_synchronization_mutex);
	quit_flag = false;
}


// ---------------------- Pause mode MANAGEMENT.

double ApplicationState::isPaused() {
	boost::mutex::scoped_lock lock(internal_data_synchronization_mutex);
	return pause_mode;
}

void ApplicationState::pressPause() {
	boost::mutex::scoped_lock lock(internal_data_synchronization_mutex);
	pause_mode = !pause_mode;
}


// ---------------------- Single step mode MANAGEMENT.


double ApplicationState::isSingleStepModeOn() {
	boost::mutex::scoped_lock lock(internal_data_synchronization_mutex);
	return single_step_mode;
}

void ApplicationState::pressSingleStep() {
	boost::mutex::scoped_lock lock(internal_data_synchronization_mutex);
	single_step_mode = !single_step_mode;
}


// ---------------------- Learning mode MANAGEMENT.


double ApplicationState::isLearningModeOn() {
	boost::mutex::scoped_lock lock(internal_data_synchronization_mutex);
	return learning_mode;
}

void ApplicationState::pressLearning() {
	boost::mutex::scoped_lock lock(internal_data_synchronization_mutex);
	learning_mode = !learning_mode;
}

void ApplicationState::setLearningModeOn() {
	boost::mutex::scoped_lock lock(internal_data_synchronization_mutex);
	learning_mode = true;
}

void ApplicationState::setLearningModeOff() {
	boost::mutex::scoped_lock lock(internal_data_synchronization_mutex);
	learning_mode = false;
}


// ---------------------- Using NCURSES mode MANAGEMENT.


double ApplicationState::usingNCURSES(){
	boost::mutex::scoped_lock lock(internal_data_synchronization_mutex);
	return using_ncurses;
}


void ApplicationState::startUsingNCURSES(){
	boost::mutex::scoped_lock lock(internal_data_synchronization_mutex);
	using_ncurses = true;
}

void ApplicationState::stopUsingNCURSES(){
	boost::mutex::scoped_lock lock(internal_data_synchronization_mutex);
	using_ncurses = false;
}


// ---------------------- Using OpenGL mode MANAGEMENT.


double ApplicationState::usingOpenGL(){
	boost::mutex::scoped_lock lock(internal_data_synchronization_mutex);
	return using_opengl;
}

void ApplicationState::startUsingOpenGL(){
	boost::mutex::scoped_lock lock(internal_data_synchronization_mutex);
	using_opengl = true;
}


void ApplicationState::stopUsingOpenGL(){
	boost::mutex::scoped_lock lock(internal_data_synchronization_mutex);
	using_opengl = false;
}



// ---------------------- SLEEP INTERVAL MANAGEMENT.


void ApplicationState::setSleepInterval(double sleep_interval_) {
	boost::mutex::scoped_lock lock(internal_data_synchronization_mutex);
	application_sleep_interval = sleep_interval_;
	// Truncate sleep interval.
	application_sleep_interval = ((application_sleep_interval < 1) ? 1 : application_sleep_interval);
	application_sleep_interval = ((application_sleep_interval > 10000000) ? 10000000 : application_sleep_interval);
}

double ApplicationState::getSleepInterval() {
	boost::mutex::scoped_lock lock(internal_data_synchronization_mutex);
	return application_sleep_interval;
}

void ApplicationState::setSleepIntervalS(double sleep_interval_in_seconds) {
	setSleepInterval(1000000*sleep_interval_in_seconds);
}

void ApplicationState::setSleepIntervalMS(double sleep_interval_in_miliseconds) {
	setSleepInterval(1000*sleep_interval_in_miliseconds);
}

void ApplicationState::setSleepIntervalUS(double sleep_interval_in_microseconds) {
	setSleepInterval(sleep_interval_in_microseconds);
}

void ApplicationState::multiplySleepInterval(double m_) {
	boost::mutex::scoped_lock lock(internal_data_synchronization_mutex);
	application_sleep_interval = application_sleep_interval * m_;
	// Truncate sleep interval.
	application_sleep_interval = ((application_sleep_interval > 10000000) ? 10000000 : application_sleep_interval);
	LOG(LSTATUS) << "Setting sleep interval to " << application_sleep_interval << " [us]";
}

void ApplicationState::divideSleepInterval(double d_) {
	boost::mutex::scoped_lock lock(internal_data_synchronization_mutex);
	application_sleep_interval = application_sleep_interval / d_;
	// Truncate sleep interval.
	application_sleep_interval = ((application_sleep_interval < 1) ? 1 : application_sleep_interval);
	LOG(LSTATUS) << "Setting sleep interval to " << application_sleep_interval << " [us]";
}


void ApplicationState::displayStatus() {
	LOG(LSTATUS) <<"----------------------------------------------------------------";
	LOG(LSTATUS) <<"Application status:";
	LOG(LSTATUS) <<"----------------------------------------------------------------";
	// Quit flag.
	LOG(LSTATUS) << "QUIT:\t\t\t" << ((quit_flag) ? "YES" : "NO");
	// Time interval.
	LOG(LSTATUS) << "SLEEP INTERVAL:\t\t" << application_sleep_interval << " [ms]";

	// Modes.
	LOG(LSTATUS) << "PAUSE MODE:\t\t" << ((pause_mode) ? "ON" : "OFF");
	LOG(LSTATUS) << "SINGLE STEP MODE:\t" << ((single_step_mode) ? "ON" : "OFF");
	LOG(LSTATUS) << "LEARNING:\t\t" << ((learning_mode) ? "ON" : "OFF");

	// Using gui/cli/visualization.
	LOG(LSTATUS) << "USING OPENGL :\t\t" << ((using_opengl) ? "YES" : "NO");
	LOG(LSTATUS) << "USING NCURSES:\t\t" << ((using_ncurses) ? "YES" : "NO");
	LOG(LSTATUS) <<"----------------------------------------------------------------";
}



} /* namespace application */
} /* namespace mic */

