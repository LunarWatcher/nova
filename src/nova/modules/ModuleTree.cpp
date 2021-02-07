#include "nova/modules/ModuleTree.hpp"

namespace nova {

std::shared_ptr<ModuleTree> ModuleTree::getInstance() {
    if (ModuleTree::INSTANCE == nullptr)
        ModuleTree::INSTANCE = std::make_shared<ModuleTree>();
    return ModuleTree::INSTANCE;
}

} // namespace nova
