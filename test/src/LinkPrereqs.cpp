#include "catch2/catch_test_macros.hpp"

#include <regex>

#include "termutil/FilesystemUtil.hpp"

TEST_CASE("Verify getExecutableLocation()", "[ExecutableLocation]") {
    std::string s;
    REQUIRE_NOTHROW(s = termutil::Filesystem::getExecutableLocation());

    REQUIRE(std::regex_match(s, std::regex("([a-zA-Z]:)?[\\\\/].*/build[\\\\/]test[\\\\/]bin[\\\\/]tests(.exe)?")));
}
