# Machine Intelligence Core: Toolchain

Status of Travis Continuous Integration:

[![Build Status](https://travis.ibm.com/tkornut/mi-toolchain.svg?token=9XHfj7QaSbmFqHsyaQes&branch=master)](https://travis.ibm.com/tkornut/mi-toolchain)

## Description

A subproject of Machine Intelligence Core, being the real "core" of the framework.

Contains tools required for development of MIC-based applications, such as configuration management, loggers, application state etc.

## MIC dependencies
   * none

## External dependencies

Additionally it depends on the following external libraries:
   * Boost - a library of free (open source) peer-reviewed portable C++ source libraries.
   * Eigen - a C++ template library for linear algebra: matrices, vectors, numerical solvers, and related algorithms.
   
### Installing the dependencies/required tools

On Linux (Ubuntu 14.04): 

    sudo apt-get install git cmake cmake-curses-gui doxygen libboost1.54-all-dev libeigen3-dev libopenblas-dev


## Main modules

   * application - classes related for management of applications, their state, keyhandlers as well application factories. 
   * configuration - classes responsible for configuration managenemt (parameters server, property tree etc.) 
   * logger - classess and functions related to logger 
   * system_utils - timers etc. (depricated)

## Applications

   * logger_test - application for testing console logger.

## Installation

```

cd workspace

git clone git@github.ibm.com:tkornut/mi-toolchain.git

cd mi-toolchain

mkdir build

cd build

cmake .. -DCMAKE_INSTALL_PREFIX=~/workspace/mic/

make -j4 install

```

## Maintainer

tkornuta


