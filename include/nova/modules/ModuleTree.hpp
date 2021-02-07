#pragma once

#include "Module.hpp"
#include <iostream>
#include <memory>

namespace nova {

class ModuleTree {
private:
    inline static std::shared_ptr<ModuleTree> INSTANCE = nullptr;

    // TODO: figure out how to best store modules.
    // Pointers all the way, though.
public:
    void registerModule(std::shared_ptr<Module> module) {
        std::cout << "Registered " << module->getName() << std::endl;
    }

    static std::shared_ptr<ModuleTree> getInstance();
};

} // namespace nova
