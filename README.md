# Machine Intelligence Core: Toolchain

![Language](https://img.shields.io/badge/language-C%2B%2B-blue.svg)
[![Build Status](https://travis-ci.com/IBM/mi-toolchain.svg?branch=master)](https://travis-ci.com/IBM/mi-toolchain)
[![GitHub license](https://img.shields.io/github/license/IBM/mi-toolchain.svg)](https://github.com/IBM/mi-toolchain/blob/master/LICENSE)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/IBM/mi-toolchain.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/IBM/mi-toolchain/alerts/)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/IBM/mi-toolchain.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/IBM/mi-toolchain/context:cpp)

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

    sudo apt-get install git cmake doxygen libboost1.54-all-dev

## Main modules

   * application - classes related for management of applications, their state, key-handlers as well application factories. 
   * configuration - classes responsible for configuration management (parameters server, property tree etc.) 
   * logger - classes and functions related to logger 

## Applications

   * logger_test - application for testing console logger.

## Installation

In order to download, configure, make and install new "clean" version of mi-toolchain please execute the following:

    cd ~/workspace
    git clone git@github.com:ibm/mi-toolchain.git
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

https://ibm.github.io/mi-toolchain/

## Maintainer

Tomasz Kornuta (tkornut@us.ibm.com)


