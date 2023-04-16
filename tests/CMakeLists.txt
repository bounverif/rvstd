find_package(Catch2 REQUIRED)

include(Catch)
include(CTest)

add_executable(
  rvstd_tests
    options.test.cpp
    forward_signal.test.cpp
    instruction.test.cpp
    unique_identifier.test.cpp
    boost_json_ext.test.cpp
)

target_link_libraries(
  rvstd_tests
    PRIVATE
      rvstd
      Catch2::Catch2WithMain
)

catch_discover_tests(rvstd_tests)
