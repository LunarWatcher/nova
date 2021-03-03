# Add library

add_library(novasources STATIC nova/input/InputProcessor.cpp nova/loading/ModLoader.cpp
    nova/modules/builtins/HelpModule.cpp nova/modules/Module.cpp nova/modules/ModuleTree.cpp
    )

add_executable(nova nova/Main.cpp)
if (WIN32 AND MSVC)
    set(NovaSourceDep -WHOLEARCHIVE:$<TARGET_FILE:novasources>)
elseif(APPLE)
    set(NovaSourceDep -Wl,-all_load novasources -Wl,-noall_load)
else()
    set(NovaSourceDep -Wl,--whole-archive novasources -Wl,--no-whole-archive)
endif()

target_link_libraries(nova PRIVATE "${NovaSourceDep}")
if (NOT WIN32)
    target_link_libraries(nova PRIVATE dl)
endif()
