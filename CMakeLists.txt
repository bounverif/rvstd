cmake_minimum_required(VERSION 3.22)

file(READ "${CMAKE_SOURCE_DIR}/include/rvstd/version.hpp" version_file)

string(
  REGEX
    MATCH
    "VERSION_MAJOR ([0-9]*)"
    _
    ${version_file}
)
set(RVSTD_VERSION_MAJOR ${CMAKE_MATCH_1})
string(
  REGEX
    MATCH
    "VERSION_MINOR ([0-9]*)"
    _
    ${version_file}
)
set(RVSTD_VERSION_MINOR ${CMAKE_MATCH_1})
string(
  REGEX
    MATCH
    "VERSION_PATCH ([0-9]*)"
    _
    ${version_file}
)
set(RVSTD_VERSION_PATCH ${CMAKE_MATCH_1})

project(
  "rvstd"
  VERSION "${RVSTD_VERSION_MAJOR}.${RVSTD_VERSION_MINOR}.${RVSTD_VERSION_PATCH}"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_COVERAGE "-O0 --coverage")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(
  CMAKE_BUILD_TYPE
  Release
  CACHE STRING "Build type"
)
set(BOOST_USE_STATIC_LIBS ON)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(BUILD_TESTING "Build tests" ON)

include(CTest)
include(GNUInstallDirs)

find_package(
  Boost 1.87
  COMPONENTS json url
  REQUIRED
)

set(
  RVSTD_SOURCES
  "src/rvstd/boost_json_ext.cpp"
  "src/rvstd/unique_identifier.cpp"
  "src/rvstd/tableau.cpp"
  "src/rvstd/options.cpp"
  "src/rvstd/resource.cpp"
)

# Static library
add_library(rvstd STATIC ${RVSTD_SOURCES} ${RYTEST_SOURCES})
target_include_directories(
  rvstd PUBLIC $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
               $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)
target_link_libraries(rvstd PUBLIC Boost::json Boost::url)

set_target_properties(rvstd PROPERTIES OUTPUT_NAME "rvstd" VERSION ${PROJECT_VERSION})

# Shared library
add_library(rvstd-shared SHARED ${RVSTD_SOURCES} ${RYTEST_SOURCES})
target_include_directories(
  rvstd-shared PUBLIC $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
                      $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)
target_link_libraries(rvstd-shared PUBLIC Boost::json Boost::url)
set_target_properties(
  rvstd-shared
  PROPERTIES
    OUTPUT_NAME "rvstd"
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Include GNUInstallDirs for standard install paths
include(GNUInstallDirs)

# Install headers
install(
  DIRECTORY ${CMAKE_SOURCE_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING
  PATTERN "*.hpp"
)

# Install targets
install(
  TARGETS rvstd
  EXPORT rvstd-config
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
  TARGETS rvstd-shared
  EXPORT rvstd-shared-config
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Export configuration
export(
  TARGETS rvstd
  NAMESPACE rvstd::
  FILE "${CMAKE_CURRENT_BINARY_DIR}/rvstd-config.cmake"
)
export(
  TARGETS rvstd-shared
  NAMESPACE rvstd::
  FILE "${CMAKE_CURRENT_BINARY_DIR}/rvstd-shared-config.cmake"
)

# Install exported configurations
install(
  EXPORT rvstd-config
  DESTINATION "${CMAKE_INSTALL_DATADIR}/rvstd/cmake"
  NAMESPACE rvstd::
)
install(
  EXPORT rvstd-shared-config
  DESTINATION "${CMAKE_INSTALL_DATADIR}/rvstd/cmake"
  NAMESPACE rvstd::
)

# Enable testing if requested
if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

# Debugging message
message(STATUS "Building rvstd version ${PROJECT_VERSION}")
