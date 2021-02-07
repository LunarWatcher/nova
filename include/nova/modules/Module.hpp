#pragma once

#include <string>
#include <vector>

namespace nova {

class Module {
protected:
    std::string name;
    std::vector<std::string> aliases;

    std::vector<std::string> subcommands;

public:
    const std::string& getName() {
        return name;
    }
};

} // namespace nova
