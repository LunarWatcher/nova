#include "nova/input/InputProcessor.hpp"

namespace nova {

std::shared_ptr<InputProcessor> InputProcessor::INSTANCE = nullptr;

void InputProcessor::parseData(int argc, char* argv[]) {

    // i = 0 is the binary call. We're ignoring this.
    for (int i = 1; i < argc; ++i) {
        std::string component{argv[i]};
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
