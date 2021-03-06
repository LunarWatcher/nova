#include "catch2/catch_test_macros.hpp"
#include "nova/loading/ModLoader.hpp"
#include "nova/modules/ModuleTree.hpp"

TEST_CASE("Base test for linking", "[LinkTest]") {
    std::string loadTarget = "test/"
#ifdef _WIN32
                             "libDemoModule.dll"
#elif defined __APPLE__
                             "libDemoModule.dylib"
#else
                             "libDemoModule.so"
#endif
            ;
    REQUIRE_NOTHROW(nova::ModLoader{}.loadDynamicLibrary(loadTarget));
    REQUIRE(nova::ModuleTree::getInstance()->getModule("destroy") != nullptr);
}
