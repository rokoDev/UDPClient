#!/bin/sh
cmake_version_id="3.18"
cmake_build_id="4"
if [ $TRAVIS_OS_NAME = linux ]
then
  sudo apt-get remove cmake
  # first we create a directory for the CMake binaries 
  DEPS_DIR="${TRAVIS_BUILD_DIR}/deps"
  mkdir ${DEPS_DIR} && cd ${DEPS_DIR}
  # we use wget to fetch the cmake binaries
  # wget --no-check-certificate "http://www.cmake.org/files/v${cmake_version_id}/cmake-$cmake_version-Linux-x86_64.tar.gz"
  curl -LOJ "http://www.cmake.org/files/v${cmake_version_id}/cmake-$cmake_version_id.$cmake_build_id-Linux-x86_64.sh"
  sudo mkdir /opt/cmake
  sudo sh cmake-$cmake_version_id.$cmake_build_id-Linux-x86_64.sh --prefix=/opt/cmake
  sudo ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake
  cmake -version
  # extract the binaries; the output here is quite lengthy,
  # so we swallow it to not clutter up the travis console
  # tar -xvf cmake-$cmake_version_id.$cmake_build_id-Linux-x86_64.tar.gz > /dev/null
  # mv cmake-$cmake_version_id.$cmake_build_id-Linux-x86_64 cmake-install
  # add both the top-level directory and the bin directory from the archive
  # to the system PATH. By adding it to the front of the path we hide the
  # preinstalled CMake with our own.
  # export PATH=${DEPS_DIR}/cmake-install:${DEPS_DIR}/cmake-install/bin:$PATH
  # cmake -version
  # don't forget to switch back to the main build directory once you are done
  cd ${TRAVIS_BUILD_DIR}
elif [ $TRAVIS_OS_NAME = osx ]
then
  cur_cmake_version=`cmake -version`
  brew update
  brew outdated cmake || brew upgrade cmake
fi