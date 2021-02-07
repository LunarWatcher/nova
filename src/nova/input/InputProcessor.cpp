#include "InputProcessor.hpp"

namespace nova {

std::shared_ptr<InputProcessor> InputProcessor::INSTANCE = nullptr;

void InputProcessor::parseData(int argc, char* argv[]) {
    int position;
    for (int i = 1; i < argc; ++i) {
        std::string component{argv[i]};
        rawComponents.push_back(component);
    }
}

std::shared_ptr<InputProcessor> InputProcessor::getInstance() {
    if (InputProcessor::INSTANCE != nullptr) {
        return InputProcessor::INSTANCE;
    }

    InputProcessor::INSTANCE = std::make_shared<InputProcessor>();
    return InputProcessor::INSTANCE;
}

} // namespace nova
