/*!
 * \file KeyHandlerRegistry.hpp
 * \brief Contains declaration of the abstract KeyHandlerRegistry class responsible for handling the keypressed callbacks.
 * \author tkornuta
 * \date Nov 20, 2015
 */

#ifndef SRC_CONFIGURATION_KEYHANDLERREGISTRY_HPP_
#define SRC_CONFIGURATION_KEYHANDLERREGISTRY_HPP_

#include <map>

#include <boost/function.hpp>
#include <boost/bind.hpp>

#include<application/ApplicationState.hpp>

#include <logger/Log.hpp>


namespace mic {
namespace application {

// function pointer type
// typedef void (*OptionFunction)(void);
//typedef std::map<char, std::pair<std::string, OptionFunction> > OptionMap_t;
//typedef std::map<char, OptionFunction > OptionMap_t;
//boost::function<void ()>    f1( boost::bind( &myclass::fun1, this ) );
//typedef std::map<char, boost::function<void ()> > OptionMap_t;


/*!
 * \brief Basic handler type representing <description, handler function> pair.
 * \author tkornuta
 */
typedef std::pair<std::string, boost::function<void ()> > Handler;

/*!
 * \brief Basic handler type representing <key, description, handler function> triplet.
 * \author tkornuta
 */
typedef std::pair<char, Handler > KeyHandler;

/*!
 * \brief Macro returning  keyhandler (key-description-handler triplet).
 * \author tkornuta
 */
#define MAKE_KEYHANDLER(KEY, DESCRIPTION, METHOD) std::make_pair((char)(KEY), std::make_pair( (DESCRIPTION), (METHOD) ) )


/*!
 * \brief Basic type storing <key, description, handler function> triplets.
 * \author tkornuta
 */
typedef std::map<char, Handler > KeyHandlerMap;

/*!
 * \brief Macro for registration of key-description-handler triplets in KeyHandlers.
 * \author tkornuta
 */
#define REGISTER_KEY_HANDLER(KEY, DESCRIPTION, METHOD) key_handler_map.insert(std::make_pair((char)(KEY), std::make_pair( (DESCRIPTION), boost::bind(METHOD, this ) ) ) )


/*!
 * \brief Abstract class responsible for handling the keypressed callbacks.
 * Implements several basic callbacks and offers several mechnisms for callback management.
 * \author tkornuta
 */
class KeyHandlerRegistry {
public:

	/*!
	 * Constructor - registers defaults handlers (quit, pause, single_step).
	 */
	KeyHandlerRegistry();

	/*!
	 * Destructor - virtual, empty for now.
	 */
	virtual ~KeyHandlerRegistry();

	/*!
	 * Handles the keypressed event.
	 * @param key_ Pressed key.
	 */
	virtual void keyboardHandler(unsigned char key);

	/*!
	 * Method for registration of user-defined handlers.
	 *
	 * @param key_ Key triggering the handler.
	 * @param description_ Handler description.
	 * @param function_ Executed function.
	 * @tparam SlotClass Template class defining the class containing the function.
	 */
	template<class SlotClass>
	void registerKeyhandler (char key_, std::string description_, void (SlotClass::*function_)(void), SlotClass *obj_ ) {
		//boost::function<void ()> f = boost::bind(function_, obj_ );
		key_handler_map.insert(std::make_pair((char)(key_), std::make_pair( (description_), boost::bind(function_, obj_ ) ) ) );
	}


	void registerKeyhandler (KeyHandler kh_) {

	}

protected:

	/*!
	 * Map of <key, description, function>.
	 */
	KeyHandlerMap key_handler_map;

	/*!
	 * Keyhandler: quits the program.
	 */
	void keyhandlerQuit(void);

	/*!
	 * Keyhandler: displays help.
	 */
	void keyhandlerDisplayOptions(void);

	/*!
	 * Keyhandler: increments the logger severity level.
	 */
	void keyhandlerIncrementLoggerLevel(void);

	/*!
	 * Keyhandler: decrements the logger severity level.
	 */
	void keyhandlerDecrementLoggerLevel(void);

	/*!
	 * Keyhandler: toggless learning on/off.
	 */
	void keyhandlerToggleLearning(void);

	/*!
	 * Keyhandler: quits the program.
	 */
	void keyhandlerPause(void);

	/*!
	 * Keyhandler: displays help.
	 */
	void keyhandlerSingleStep(void);

	/*!
	 * Keyhandler: slows down the processing (multiplies the sleep interval by 1.5).
	 */
	void keyhandlerSlowDown(void);

	/*!
	 * Keyhandler: fastens up the processing (divides the sleep interval by 1.5).
	 */
	void keyhandlerFastenUp(void);

	/*!
	 * Keyhandler: resets the processing time (sets the sleep interval to 1s).
	 */
	void keyhandlerResetProcessingTime(void);

	/*!
	 * Keyhandler: display application status.
	 */
	void keyhandlerDisplayAppState(void);

};

} /* namespace application */
} /* namespace mic */

#endif /* SRC_CONFIGURATION_KEYHANDLERREGISTRY_HPP_ */
