cmake_minimum_required(VERSION 3.8)
set (CMAKE_CXX_STANDARD 17)
set (CXX_STANDARD_REQUIRED true)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Setting up project
project(SOjsonAssign)

# Output dirs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(SOjsonAssign_INCLUDE_BUILD_DIR "${PROJECT_SOURCE_DIR}/include/")
set(SOjsonAssign_SRC_BUILD_DIR "${PROJECT_SOURCE_DIR}/src/")


set(SOjsonAssign_TARGET_NAME               ${PROJECT_NAME})

# The version number.
# Set the version number of your project here (format is MAJOR.MINOR.PATCHLEVEL - e.g. 1.0.0)
set(VERSION_MAJOR "0")
set(VERSION_MINOR "4")
set(VERSION_PATCH "0")
set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

##
## OPTIONS
##
option(BUILDTESTS "Build the unit tests when BUILD_TESTING is enabled." OFF)

## Git (and its revision)
find_package(Git QUIET) # if we don't find git or FindGit.cmake is not on the system we ignore it.
## GetGitRevisionDescription module to retreive branch and revision information from Git
## Starting with Git 1.9 the module will be part of official cMake distribution, until then it has to be
## part of the application
## The Git module will trigger a reconfiguration for each pull that will bring a new revision on the local repository
set (VCS_REVISION "-1")
if(GIT_FOUND)
    if(EXISTS ${CMAKE_SOURCE_DIR}/.git)
    include(GetGitRevisionDescription)
    get_git_head_revision(GIT_REFSPEC GIT_SHA1)
    git_get_exact_tag(GIT_TAG)
    if(GIT_TAG EQUAL "-128-NOTFOUND")
        set (GIT_TAG "none")
    endif()
    message(STATUS "GIT branch ${GIT_REFSPEC}")
    message(STATUS "GIT revision ${GIT_SHA1}")
    message(STATUS "GIT tag ${GIT_TAG}")
    set (VCS_REVISION ${GIT_SHA1})
    else()
         message(STATUS "No git repository.")
    endif()
endif()

# Produce the final Version.h using template Version.h.in and substituting variables.
# We don't want to polute our source tree with it, thus putting it in binary tree.
configure_file("include/SOjsonAssign/SOjsonAssignVersion.h.in" "${CMAKE_CURRENT_BINARY_DIR}/SOjsonAssignVersion.h" @ONLY)

# This sets the include directory for the reference project. This is the -I flag in gcc.
# All the includes should be in this variable To add new directories to the include path,
# just add them in this list (after a space), or add an include_directories statement in a
# subdirectory's CMakeLists.
include_directories(
    ${PROJECT_SOURCE_DIR}/ext/json/single_include
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/include   # add the binary tree to the search path so that we will find Version.h
)


add_subdirectory(src)


##
## TESTS
## create and configure the unit test target
##
include(CTest) #adds option BUILD_TESTING (default ON)

if(BUILD_TESTING AND BUILDTESTS)
    enable_testing()
    add_subdirectory(test)
endif()

#
# SYSTEM PACKAGING (RPM, TGZ, ...)
# _____________________________________________________________________________

#include(CPackConfig)

#
# CMAKE PACKAGING (for other CMake projects to use this one easily)
# _____________________________________________________________________________

#include(PackageConfigurator)
