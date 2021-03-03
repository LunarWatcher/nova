add_executable(tests src/TestRunner.cpp src/TestLinking.cpp src/ModuleTreeTest.cpp
                     src/LinkPrereqs.cpp)
target_link_libraries(tests PUBLIC ${LinkNova} Catch2::Catch2)

add_library(DemoModule SHARED src/modules/DemoModule.cpp)

add_dependencies(tests DemoModule)
