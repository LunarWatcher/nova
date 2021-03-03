#include "nova/dynamic/DynHelper.hpp"
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

NOVA_EXPORT void NovaMain() {
    nova::ModuleTree::getInstance()->registerModule(std::make_shared<SuperAwesomeDestroyerClassSpaceShip::Destroyer>());
}
