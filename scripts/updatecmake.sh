#!/bin/sh
cmake_version_id="3.18"
cmake_version="3.18.4"
if [ "$TRAVIS_OS_NAME" == "linux" ]
then
  # first we create a directory for the CMake binaries 
  DEPS_DIR="${TRAVIS_BUILD_DIR}/deps"
  mkdir ${DEPS_DIR} && cd ${DEPS_DIR}
  # we use wget to fetch the cmake binaries
  travis_retry wget --no-check-certificate "http://www.cmake.org/files/v${cmake_version_id}/cmake-$cmake_version-Linux-x86_64.tar.gz"
  # extract the binaries; the output here is quite lengthy,
  # so we swallow it to not clutter up the travis console
  tar -xvf cmake-$cmake_version-Linux-x86_64.tar.gz > /dev/null
  mv cmake-$cmake_version-Linux-x86_64 cmake-install
  # add both the top-level directory and the bin directory from the archive
  # to the system PATH. By adding it to the front of the path we hide the
  # preinstalled CMake with our own.
  PATH=${DEPS_DIR}/cmake-install:${DEPS_DIR}/cmake-install/bin:$PATH
  # don't forget to switch back to the main build directory once you are done
  cd ${TRAVIS_BUILD_DIR}
elif [ $TRAVIS_OS_NAME = osx ]
then
  cur_cmake_version=`cmake -version`
  echo "cur_cmake_version: $cur_cmake_version"
  #brew update
  echo "brew outdated cmake || brew upgrade cmake"
  brew outdated cmake || brew upgrade cmake
fi