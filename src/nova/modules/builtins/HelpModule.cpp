#include "nova/modules/builtins/HelpModule.hpp"

namespace nova {

HelpModule::HelpModule() {
    this->name = "help";
    this->aliases = {"info"};
}

} // namespace nova
