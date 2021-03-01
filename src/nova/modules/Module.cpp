#include "nova/modules/Module.hpp"

#include <algorithm>

namespace nova {

bool Module::isSubcommand(const std::string& command) {
    return std::find(subcommands.begin(), subcommands.end(), command) != subcommands.end();
}

} // namespace nova
