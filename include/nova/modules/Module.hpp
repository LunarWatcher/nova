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
    virtual ~Module() = default;
    virtual const std::string& getName() {
        return name;
    }

    virtual bool isSubcommand(const std::string& command);
};

} // namespace nova
