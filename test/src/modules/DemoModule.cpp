#include "nova/modules/Module.hpp"
#include "nova/modules/ModuleTree.hpp"

namespace SuperAwesomeDestroyerClassSpaceShip {

class Destroyer : public nova::Module {
public:
    Destroyer() {
        this->name = "destroy";
        this->aliases = {"delete", "exterminate", "big-ass-boom"};
    }
};

} // namespace SuperAwesomeDestroyerClassSpaceShip
#include <iostream>
void NovaMain() {
    std::cout << "hi";
    nova::ModuleTree::getInstance()->registerModule(std::make_shared<SuperAwesomeDestroyerClassSpaceShip::Destroyer>());
}
