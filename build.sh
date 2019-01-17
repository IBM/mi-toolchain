# Copyright (C) tkornuta, IBM Corporation 2015-2019
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Configure cmake and prepare installation dir.
mkdir $TRAVIS_BUILD_DIR/../mic/
mkdir build
cd build
# Overwrite compiler!
if [[ "${COMPILER}" != "" ]]; then export CXX=${COMPILER}; fi
cmake .. -DCMAKE_INSTALL_PREFIX=$TRAVIS_BUILD_DIR/../mic/
# Build and install.
make install VERBOSE=1
