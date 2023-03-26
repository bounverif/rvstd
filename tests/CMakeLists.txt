find_package(Catch2 REQUIRED)

include(Catch)
include(CTest)

add_executable(
  rvstd_tests
    instruction.test.cpp
    unique_identifier.test.cpp
)

target_link_libraries(
  rvstd_tests
    PRIVATE
      rvstd
      Catch2::Catch2WithMain
)

catch_discover_tests(rvstd_tests)
