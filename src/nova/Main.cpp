#include "nova/input/InputProcessor.hpp"
#include "nova/loading/ModLoader.hpp"
#include "termutil/ColorPrinter.hpp"
#include "termutil/FilesystemUtil.hpp"

int main(int argc, char* argv[]) {
    try {
        if (argc == 1) {
            termutil::ColorPrinter printer;
            printer << termutil::ANSIFeature::FOREGROUND << 12 << "Hello! how can I help?"
                    << termutil::ANSIFeature::CLEAR << std::endl;
        } else {

            try {
                nova::InputProcessor& processor = *nova::InputProcessor::getInstance();
                processor.parseData(argc, argv);
            } catch (const std::string& err) {
                termutil::ColorPrinter printer;
                printer << termutil::ANSIFeature::FOREGROUND << 9 << err << std::endl;
            }
        }
    } catch (const std::string& err) { std::cerr << err << std::endl; }

    return 0;
}
