#include <unistd.h>

#include <cstdlib>
#include <iostream>

#include "input/InputProcessor.hpp"
#include "termutil/ColorPrinter.hpp"

int main(int argc, char* argv[]) {
    if (argc == 1) {
        termutil::ColorPrinter printer;
        printer << termutil::ANSIFeature::FOREGROUND << 12 << "Hello! how can I help?" << termutil::ANSIFeature::CLEAR
                << std::endl;
    } else {

        try {
            nova::InputProcessor& processor = *nova::InputProcessor::getInstance();
        } catch (const std::string& err) {
            termutil::ColorPrinter printer;
            printer << termutil::ANSIFeature::FOREGROUND << 9 << err << std::endl;
        }
    }

    return 0;
}
