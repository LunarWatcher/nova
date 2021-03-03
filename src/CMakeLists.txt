# Add library

add_library(novasources STATIC nova/input/InputProcessor.cpp nova/loading/ModLoader.cpp
    nova/modules/builtins/HelpModule.cpp nova/modules/Module.cpp nova/modules/ModuleTree.cpp
    )
if (NOT WIN32)
    target_link_libraries(novasources PUBLIC dl)
endif()


# Build nova
add_executable(nova nova/Main.cpp)

# We then wanna link it properly
if (WIN32 AND MSVC)
    set(NovaSourceDep -WHOLEARCHIVE:$<TARGET_FILE:novasources>)
elseif(APPLE)
    set(NovaSourceDep -Wl,-all_load novasources -Wl,-noall_load)
else()
    set(NovaSourceDep -Wl,--whole-archive novasources -Wl,--no-whole-archive)
endif()

set(LinkNova ${NovaSourceDep} PARENT_SCOPE)
target_link_libraries(nova PRIVATE "${NovaSourceDep}")
