add_definitions(-D__LIBNAME="SOjsonAssign")

# We need profiling info if tests are activated
if(BUILD_TESTING AND SOjsonAssign_BuildTests)
    set(CMAKE_CXX_FLAGS "--coverage -g -O0 -fprofile-arcs -ftest-coverage")
endif()


set(LIB_HEADERS
  "${CMAKE_CURRENT_BINARY_DIR}/../include/SOjsonAssign/SOjsonAssignVersion.h" # Generated header
  ../include/SOjsonAssign/BaseClass.h
)

set(LIB_SOURCES
)

set(APP_HEADERS
)

set(APP_SOURCES
  main.cpp
)

include_directories("${CMAKE_SOURCE_DIR}/include/SOjsonAssign"
  )

# Uncomment if you need threads
# set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
# set(THREADS_PREFER_PTHREAD_FLAG TRUE)
# find_package(Threads REQUIRED)

# This is a make target, so you can do a "make SOjsonAssignrunner"
set(APPLICATION_NAME SOjsonAssignrunner)
add_executable(${APPLICATION_NAME} ${APP_SOURCES})

# Links the target exe (projArunner) against the library (libprojA) and other required libraries
target_link_libraries(${APPLICATION_NAME})
#

# Says how and where to install software
# Targets:
#   * <prefix>/lib/<libraries>
#   * header location after install: <prefix>/include/<project>/*.h
#   * headers can be included by C++ code `#<project>/Bar.hpp>`
install(TARGETS ${APPLICATION_NAME}
  EXPORT ${PROJECT_NAME}Targets            # for downstream dependencies
  ARCHIVE DESTINATION lib COMPONENT libs   # static lib
  RUNTIME DESTINATION bin COMPONENT libs   # binaries
  LIBRARY DESTINATION lib COMPONENT libs   # shared lib
  FRAMEWORK DESTINATION bin COMPONENT libs # for mac
  PUBLIC_HEADER DESTINATION include/${PROJECT_NAME} COMPONENT devel   # headers for mac (note the different component -> different package)
  INCLUDES DESTINATION include             # headers
)
