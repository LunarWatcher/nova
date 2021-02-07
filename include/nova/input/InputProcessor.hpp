#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace nova {

class InputProcessor {
private:
    static std::shared_ptr<InputProcessor> INSTANCE;

    std::vector<std::string> rawComponents;
    std::map<std::string, std::string> dataMap;

public:
    void parseData(int argc, char* argv[]);

    static std::shared_ptr<InputProcessor> getInstance();
};

} // namespace nova
