#include "nova/modules/Module.hpp"
#include "nova/modules/ModuleTree.hpp"

class MyModule : public nova::Module {
public:
    MyModule() {
        this->name = "FUCK YEAH!";
    }
};

extern "C" {
__attribute__((visibility("default"))) void NovaMain() {
    nova::ModuleTree::getInstance()->registerModule(std::make_shared<MyModule>());
}
}
