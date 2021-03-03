# Add library

add_library(novasources STATIC nova/input/InputProcessor.cpp nova/loading/ModLoader.cpp
    nova/modules/builtins/HelpModule.cpp nova/modules/Module.cpp nova/modules/ModuleTree.cpp
    )

add_executable(nova nova/Main.cpp)
if (WIN32)
    set(NovaSourceDep /WHOLEARCHIVE:$<TARGET_FILE:novasources>)
elseif(APPLE)
    set(NovaSourceDep -Wl,-all_load novasources -Wl,-noall_load)
else()
    set(NovaSourceDep -Wl,--whole-archive novasources -Wl,--no-whole-archive)
endif()

if (NOT WIN32)

    target_link_libraries(nova PRIVATE ${NovaSourceDep} dl)
else()
    target_link_libraries(nova PRIVATE novasources)
    get_target_property(VAR exec LINK_FLAGS)
    if ("${VAR}" STREQUAL "VAR-NOTFOUND")
        set_target_properties(nova PROPERTIES LINK_FLAGS "/WHOLEARCHIVE:novasources")
    else()
        set_target_properties(nova PROPERTIES LINK_FLAGS "${exec} /WHOLEARHIVE:novasources")
    endif()
endif()
