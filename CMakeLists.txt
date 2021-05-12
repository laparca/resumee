cmake_minimum_required(VERSION 3.18)
project(resumee VERSION 0.1)

include(cmake/CPM.cmake)

CPMAddPackage(
    NAME cpptemplater
    GIT_REPOSITORY https://git.ctrlz.es/lazycoders/cpptemplater.git 
    GIT_TAG master
    )

CPMAddPackage(
    NAME yaml-cpp
    GITHUB_REPOSITORY jbeder/yaml-cpp
    GIT_TAG yaml-cpp-0.6.3
    OPTIONS
      "YAML_CPP_BUILD_TESTS OFF"
      "YAML_CPP_BUILD_TOOLS OFF"
      "YAML_CPP_INSTALL OFF"
    )
#CPMAddPackage(
#    NAME Format.cmake
#    VERSION 1.6
#    GITHUB_REPOSITORY TheLartians/Format.cmake
#    OPTIONS # enable cmake formatting (optional)
#      "FORMAT_CHECK_CMAKE ON"
#      # path to exclude (optional, supports regular expressions)
#      "CMAKE_FORMAT_EXCLUDE cmake/CPM.cmake"
#    )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)

