#pragma once

#include <string>
#include <vector>

namespace nova {

class Module {
private:
    std::string name;
    std::vector<std::string> aliases;

    std::vector<std::string> subcommands;
};

} // namespace nova
