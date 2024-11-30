CMAKE_MINIMUM_REQUIRED(VERSION 3.22)

PROJECT("rvstd"
  VERSION 0.3.0
  LANGUAGES CXX
)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(CMAKE_CXX_FLAGS_COVERAGE "-O0 --coverage")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(CMAKE_BUILD_TYPE Release)

# Options
OPTION(ENABLE_TESTS "Enable building tests" ON)

FIND_PACKAGE(
  Boost 1.82 COMPONENTS json REQUIRED
)

set(RVSTD_SOURCES
  "src/rvstd/boost_json_ext.cpp"
  "src/rvstd/envsubst.cpp"
  "src/rvstd/unique_identifier.cpp"
  "src/rvstd/tableau.cpp"
  "src/rvstd/options.cpp"
  "src/rvstd/resource.cpp"
)

# Static library
add_library(rvstd STATIC ${RVSTD_SOURCES})
target_include_directories(rvstd
  PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)
target_link_libraries(rvstd PRIVATE Boost::json)

set_target_properties(rvstd PROPERTIES
  OUTPUT_NAME "rvstd"
  VERSION ${PROJECT_VERSION}
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# Shared library
add_library(rvstd-shared SHARED ${RVSTD_SOURCES})
target_include_directories(rvstd-shared
  PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)
target_link_libraries(rvstd-shared PUBLIC Boost::json)
set_target_properties(rvstd-shared PROPERTIES
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
  FILES_MATCHING PATTERN "*.hpp"
)

# Install targets
install(
  TARGETS rvstd
  EXPORT rvstd-config
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
  TARGETS rvstd-shared
  EXPORT rvstd-shared-config
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
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
if(ENABLE_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

# Debugging message
message(STATUS "Building rvstd version ${PROJECT_VERSION}")
