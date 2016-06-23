/*!
 * \file ApplicationState.hpp
 * \brief ApplicationState declaration.
 * \author tkornuta
 * \date Nov 16, 2015
 */

#ifndef SRC_CONFIGURATION_APPLICATIONSTATE_HPP_
#define SRC_CONFIGURATION_APPLICATIONSTATE_HPP_

#include <boost/atomic.hpp>
#include <boost/thread/mutex.hpp>

#include <configuration/PropertyTree.hpp>
#ifdef _WIN32
#include <system_utils/windows_extras.hpp> // extra windows stuff
#endif

namespace mic {

/*!
 * \namespace mic::application
 * \brief Contains base application-related classes, types and types.
 * \author tkornuta
 */
namespace application {

/*!
 * Forward declaration of the application class.
 */
class Application;

/*!
 * \brief Class storing the state of the application (modes, sleep interval etc.).
 * Defined in the form of a singleton, with double-checked locking pattern (DCLP) based access to instance.
 * \author tkornuta
 */
class ApplicationState : public configuration::PropertyTree {
public:
	/*!
	 * Method for accessing the object instance, with double-checked locking optimization.
	 * @return Instance of ApplicationState singleton.
	 */
	static ApplicationState* getInstance();

	// ---------------------- Quit flag MANAGEMENT.

	/*!
	 * Returns quit flag state.
	 * Access secured with scoped lock.
	 * @return Quit flag state.
	 */
	double Quit();

	/*!
	 * Change the state of quit flag to true.
	 * Access secured with scoped lock.
	 */
	void setQuit();

	/*!
	 * Change the state of quit flag to false.
	 * Access secured with scoped lock.
	 */
	void resetQuit();

	// ---------------------- Single step flag MANAGEMENT.

	/*!
	 * Returns pause_mode flag state.
	 * Access secured with scoped lock.
	 * @return Pause_mode state.
	 */
	double isPaused();

	/*!
	 * Change the state of pause_mode flag, as flag is "bimodal", then acts as pressing "pause" button in e.g. VCR (turns it on/off).
	 * Access secured with scoped lock.
	 */
	void pressPause();

	// ---------------------- Single step mode MANAGEMENT.

	/*!
	 * Returns single_step_mode flag state.
	 * Access secured with scoped lock.
	 * @return single_step_mode state.
	 */
	double isSingleStepModeOn();

	/*!
	 * Change the state of single_step_mode flag, as flag is "bimodal", then acts as pressing "pause" button in e.g. VCR (turns it on/off).
	 * Access secured with scoped lock.
	 */
	void pressSingleStep();

	// ---------------------- Learning mode MANAGEMENT.

	/*!
	 * Returns learning_mode flag state.
	 * Access secured with scoped lock.
	 * @return learning_mode state.
	 */
	double isLearningModeOn();

	/*!
	 * Change the state of learning_mode flag, as flag is "bimodal", then acts as pressing "pause" button in e.g. VCR (turns it on/off).
	 * Access secured with scoped lock.
	 */
	void pressLearning();

	/*!
	 * Change the state of learning_mode to true.
	 * Access secured with scoped lock.
	 */
	void setLearningModeOn();

	/*!
	 * Change the state of learning_mode to false.
	 * Access secured with scoped lock.
	 */
	void setLearningModeOff();

	// ---------------------- Using NCURSES mode MANAGEMENT.

	/*!
	 * Returns using_ncurses flag state.
	 * Access secured with scoped lock.
	 * @return using_ncurses state.
	 */
	double usingNCURSES();

	/*!
	 * Sets using_ncurses flag.
	 * Access secured with scoped lock.
	 */
	void startUsingNCURSES();

	/*!
	 * Resets using_ncurses flag.
	 * Access secured with scoped lock.
	 */
	void stopUsingNCURSES();


	// ---------------------- Using OpenGL mode MANAGEMENT.

	/*!
	 * Returns using_opengl flag state.
	 * Access secured with scoped lock.
	 * @return using_opengl state.
	 */
	double usingOpenGL();

	/*!
	 * Sets using_opengl flag.
	 * Access secured with scoped lock.
	 */
	void startUsingOpenGL();

	/*!
	 * Resets using_opengl flag.
	 * Access secured with scoped lock.
	 */
	void stopUsingOpenGL();


	// ---------------------- SLEEP INTERVAL MANAGEMENT.

	/*!
	 * Returns current value of time interval.
	 * Access secured with scoped lock.
	 * @return Sleep interval
	 */
	double getSleepInterval();

	/*!
	 * Sets new value of sleep interval (in s).
	 * @param sleep_interval_in_seconds New value of sleep interval [s].
	 */
	void setSleepIntervalS(double sleep_interval_in_seconds);

	/*!
	 * Sets new value of sleep interval (in ms).
	 * @param sleep_interval_in_miliseconds New value of sleep interval [ms].
	 */
	void setSleepIntervalMS(double sleep_interval_in_miliseconds);

	/*!
	 * Sets new value of sleep interval (in us).
	 * @param sleep_interval_in_microseconds New value of sleep interval [us].
	 */
	void setSleepIntervalUS(double sleep_interval_in_microseconds);

	/*!
	 * Increases the sleep interval by multiplying it by a given value.
	 * Access secured with scoped lock.
	 * @param m_ Multiplier.
	 */
	void multiplySleepInterval(double m_ = 1.5);

	/*!
	 * Decreases the sleep interval by dividing it by a given value.
	 * Access secured with scoped lock.
	 * @param d_ Divisor.
	 */
	void divideSleepInterval(double d_ = 1.5);

	/*!
	 * Displays (with the use of logger) current status of AppState variables.
	 */
	void displayStatus();

	/*!
	 * Grants access to data synchronization mutex.
	 */
	boost::mutex & dataSynchronizationMutex() {
		return external_data_synchronization_mutex;
	}

	/*!
	 *  Registers application in APP_STATE.
	 */
	void setApplication(mic::application::Application *application_);

  	/// Property: single step mode.
	mic::configuration::Property<bool> single_step_mode;

private:
    /*!
     * Private instance - accessed as atomic operation.
     */
	static boost::atomic<ApplicationState*> instance_;

	/*!
	 * Mutex used for instantiation of the instance.
	 */
	static boost::mutex instantiation_mutex;

	/*!
	 * Mutex used synchronization of data access stored in application state (flags, internal variabies etc.).
	 */
	static boost::mutex internal_data_synchronization_mutex;

	/*!
	 * Mutex used synchronization of _external_ data (e.g. access to data from different threads such as processing and visualization threads).
	 */
	static boost::mutex external_data_synchronization_mutex;


    /// Quit application flag.
	bool quit_flag;

	/// Property: pause application mode.
	mic::configuration::Property<bool> pause_mode;

	/// Property: learning/testing mode.
	mic::configuration::Property<bool> learning_mode;

	/// Flag denoting whether application is using NCurses-based CLI.
	bool using_ncurses;

	/// Flag denoting whether application is using OpenGL-based visualization.
	bool using_opengl;


	/*!
	 * Property: sleep interval in [ms], used for slowing/fastening the computations.
	 * The interval belongs to the range between <1ms, 10s>.
	 * Set to 1000.0 (1s) by default.
	 */
	mic::configuration::Property<double> application_sleep_interval;

	/*!
	 * Private constructor. Sets default values of all flags (FALSE).
	 */
	ApplicationState();

	/*!
	 * Sets new value of sleep interval.
	 * Access secured with scoped lock.
	 * @param sleep_interval_ New value of sleep interval (in ms).
	 */
	void setSleepInterval(double sleep_interval_);

	/*!
	 * Method responsible for initialization of all variables that are property-dependent - here not required, yet empty.
	 */
	virtual void initializePropertyDependentVariables() { };

	/*!
	 * Pointer to the currently executed application.
	 */
	mic::application::Application *application;

};

/*!
 * \brief Macro returning application state instance.
 * \author tkornuta
 */
#define APP_STATE mic::application::ApplicationState::getInstance()


/*!
 * \brief Macro which sleeps the application for a time specified by the sleep_interval variable stored in APP_STATE.
 * \author tkornuta
 */
#define APP_SLEEP() usleep(APP_STATE->getSleepInterval())


/*!
 * \brief Macro creating a scoped lock with the use of data_synchronizaton_mutex stored by WindowManager.
 * \author tkornuta
 */
#define APP_DATA_SYNCHRONIZATION_SCOPED_LOCK() boost::mutex::scoped_lock lock(APP_STATE->dataSynchronizationMutex())

} /* namespace application */
} /* namespace mic */




#endif /* SRC_CONFIGURATION_APPLICATIONSTATE_HPP_ */
