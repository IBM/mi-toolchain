# Machine Intelligence Core: Toolchain

![Language](https://img.shields.io/badge/language-C%2B%2B-blue.svg)
[![GitHub license](https://img.shields.io/github/license/IBM/mi-toolchain.svg)](https://github.com/IBM/mi-toolchain/blob/master/LICENSE)
![](https://img.shields.io/github/release/IBM/mi-toolchain.svg)
[![Build Status](https://travis-ci.com/IBM/mi-toolchain.svg?branch=master)](https://travis-ci.com/IBM/mi-toolchain)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/IBM/mi-toolchain.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/IBM/mi-toolchain/context:cpp)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/IBM/mi-toolchain.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/IBM/mi-toolchain/alerts/)

## Description

A subproject of Machine Intelligence Core, being the real "core" of the framework.

Contains tools required for development of MIC-based applications, such as configuration management, properties, loggers, application state, event handlers etc.

### Main modules

   * application - classes related for management of applications, their state, key-handlers as well application factories. 
   * configuration - classes responsible for configuration management (parameters server, property tree etc.) 
   * logger - classes and functions related to logger 

### Applications

   * logger_test - application for testing console logger.

## External dependencies

Additionally it depends on the following external libraries:
   * Boost - library of free (open source) peer-reviewed portable C++ source libraries.
   * Doxygen (optional) - Tool for generation of documentation.
   * GTest (optional) - Framework for unit testing.

### Installation of the dependencies/required tools

#### On Linux (Ubuntu 14.04):

    sudo apt-get install git cmake doxygen libboost1.54-all-dev

To install GTest on Ubuntu:

    sudo apt-get install libgtest-dev

#### On Mac (OS X 10.14): (last tested on: Feb/01/2019)

    brew install git cmake doxygen boost

To install GTest on Mac OS X:

    brew install --HEAD https://gist.githubusercontent.com/Kronuz/96ac10fbd8472eb1e7566d740c4034f8/raw/gtest.rb

### Installation of MI-toolchain
The following assumes that all MIC modules will be installed to the directory '../mic'.

    git clone git@github.com:IBM/mi-toolchain.git
    cd mi-toolchain
    ./scripts/build_mic_module.sh ../mic

### Make commands

   * make install - install applications to ../mic/bin, headers to ../mic/include, libraries to ../mic/lib, cmake files to ../mic/share

## Documentation

In order to locally generate a "living" documentation of the code please run Doxygen:

    cd ~/workspace/mi-toolchain
    doxygen mi-toolchain.doxyfile
    firefox html/index.html

The current documentation (generated straight from the code and automatically uploaded to github pages by Travis) is available at:

https://ibm.github.io/mi-toolchain/

Maintainer
----------
[tkornuta][github.com/tkornut]

## Maintainer

Tomasz Kornuta (tkornut@us.ibm.com)

[![HitCount](http://hits.dwyl.io/tkornut/ibm/mi-toochain.svg)](http://hits.dwyl.io/tkornut/ibm/mi-toochain)