add_executable(tests src/TestRunner.cpp src/TestLinking.cpp src/ModuleTreeTest.cpp
                     src/LinkPrereqs.cpp)
target_link_libraries(tests PUBLIC novasources Catch2::Catch2)
