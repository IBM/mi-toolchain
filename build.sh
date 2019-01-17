# Configure cmake and prepare installation dir.
mkdir $TRAVIS_BUILD_DIR/../mic/
mkdir build
cd build
# Overwrite compiler!
if [[ "${COMPILER}" != "" ]]; then export CXX=${COMPILER}; fi
cmake .. -DCMAKE_INSTALL_PREFIX=$TRAVIS_BUILD_DIR/../mic/
# Build and install.
make install VERBOSE=1
