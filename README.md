Machine Intelligence Core: Toolchain
=========================================

Description
-----------

A subproject of Machine Intelligence Core, being the main library of the framework.

Contains tools required for development of MIC-based applications, such as configuration management, loggers, application state etc.

MIC dependencies
------------
   * none

External dependencies
------------
Additionally it depends on the following external libraries:
   * Boost - library of free (open source) peer-reviewed portable C++ source libraries.

Main modules
------------
   * application - classes related for management of applications, their state, keyhandlers as well application factories. 
   * configuration - classes responsible for configuration managenemt (parameters server, property tree etc.) 
   * logger - classess and functions related to logger 
   * system_utils - timers etc. (depricated)

Applications
------------
   * logger_test application for testing console logger

Maintainer
----------

tkornuta


