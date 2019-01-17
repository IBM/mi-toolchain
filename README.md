#Machine Intelligence Core: Toolchain

Status of Travis Continuous Integration:

[![Build Status](https://travis-ci.com/IBM/mi-toolchain.svg?branch=master)](https://travis-ci.com/IBM/mi-toolchain)

## Description

A subproject of Machine Intelligence Core, being the real "core" of the framework.

Contains tools required for development of MIC-based applications, such as configuration management, loggers, application state etc.

## MIC dependencies

   * none

## External dependencies

Toolchain depends on the following external libraries:
   * Boost - a library of free (open source) peer-reviewed portable C++ source libraries.

### Installation of the dependencies/required tools

On Linux (Ubuntu 14.04): 

    sudo apt-get install git cmake cmake-curses-gui doxygen libboost1.54-all-dev libeigen3-dev

## Main modules

   * application - classes related for management of applications, their state, key-handlers as well application factories. 
   * configuration - classes responsible for configuration management (parameters server, property tree etc.) 
   * logger - classess and functions related to logger 

## Applications

   * logger_test - application for testing console logger.

## Installation

In order to download, configure, make and install new "clean" version of mi-toolchain please execute the following:

    cd ~/workspace
    git clone git@github.ibm.com:tkornut/mi-toolchain.git
    cd mi-toolchain
    mkdir build
    cd build
    cmake .. -DCMAKE_INSTALL_PREFIX=~/workspace/mic/
    make -j4 install

## Documentation

In order to generate a "living" documentation of the code please run Doxygen:

    cd ~/workspace/mi-toolchain
    doxygen mi-toolchain.doxyfile
    firefox html/index.html

The current documentation (generated straight from the code and automatically uploaded to GH pages by Travis) is available at:

https://pages.github.ibm.com/tkornut/mi-toolchain/

## Maintainer

Tomasz Kornuta (tkornut@us.ibm.com)


