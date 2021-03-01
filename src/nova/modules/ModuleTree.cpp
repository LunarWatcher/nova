#include "nova/modules/ModuleTree.hpp"
#include <memory>
#include <sstream>
#include <variant>

namespace nova {

void ModuleTree::registerModule(std::shared_ptr<Module> module, const std::vector<std::string>& path) {
    if (module == nullptr) {
        return;
    }

    if (path.size() == 0) {
        // Largely for overriding purposes
        std::shared_ptr<ModuleNode> node = std::make_shared<ModuleNode>();
        node->module = module;
        this->registeredModules[module->getName()] = node;
        return;
    }
    auto node = this->resolvePath(path);
    auto moduleNode = std::make_shared<ModuleNode>();
    moduleNode->module = module;
    // path.size() is never nullptr, so node will never be null.
    node->add(module->getName(), moduleNode);
}

bool ModuleTree::registerAlias(
        const std::string& target, const std::string& alias, const std::vector<std::string>& path) {
    if (path.size() == 0) {
        if (this->registeredModules.find(alias) == this->registeredModules.end()) {
            this->registeredModules[alias] = target;
            return true;
        }
        return false;
    }

    auto node = this->resolvePath(path);
    return node->add(target, alias);
}

bool ModuleNode::add(const std::string& k, std::shared_ptr<ModuleNode> node) {
    auto ptr = children.find(k);
    if (ptr == children.end()) {
        children[k] = node;
        return true;
    }
    auto& var = children[k];
    if (!std::holds_alternative<std::string>(var)) {
        return false;
    }
    var = node;
    return true;
}

bool ModuleNode::add(const std::string& k, const std::string& node) {
    auto ptr = children.find(k);
    if (ptr == children.end()) {
        children[k] = node;
        return true;
    }
    // We'll skip existing aliases as well as modules. We NEVER override modules, and overriding other aliases
    // may have side-effects.
    return false;
}

std::shared_ptr<ModuleTree> ModuleTree::getInstance() {
    if (ModuleTree::INSTANCE == nullptr)
        ModuleTree::INSTANCE = std::make_shared<ModuleTree>();
    return ModuleTree::INSTANCE;
}

std::shared_ptr<ModuleNode> ModuleNode::findNode(ModuleTreeMap& haystack, const std::string& key) {
    // Empty map
    if (haystack.size() == 0) {
        return nullptr;
    }
    // Key not found
    if (haystack.find(key) == haystack.end()) {
        return nullptr;
    }
    auto& nextNode = haystack[key];
    // Contains a string; to prevent recursion, we call
    // this alias bad and ignore it.
    if (std::holds_alternative<std::string>(nextNode)) {
        auto nextKey = std::get<std::string>(nextNode);
        if (haystack.find(nextKey) == haystack.end()) {
            return nullptr;
        }
        auto& nestedNode = haystack[nextKey];
        if (std::holds_alternative<std::string>(nestedNode)) {
            return nullptr;
        }
        return std::get<std::shared_ptr<ModuleNode>>(nestedNode);
    }
    // If all the above checks pass, we have a good entry.
    return std::get<std::shared_ptr<ModuleNode>>(nextNode);
}

std::shared_ptr<Module> ModuleTree::getModule(const std::string& moduleName, const std::vector<std::string>& path) {
    auto module = resolvePath(path);
    if (module == nullptr) {
        auto ptr = ModuleNode::findNode(this->registeredModules, moduleName);
        return ptr == nullptr ? nullptr : ptr->module;
    }
    auto tryResolve = (*module)[moduleName];
    if (tryResolve == nullptr) {
        return nullptr;
    }

    return (*module)[moduleName]->module;
}

std::shared_ptr<ModuleNode> ModuleTree::resolvePath(std::vector<std::string> path) {
    if (path.size() == 0)
        return nullptr;

    std::string currPath = path.front();
    path.erase(path.begin());
    std::shared_ptr<ModuleNode> root = ModuleNode::findNode(this->registeredModules, currPath);
    if (!root) {
        // compensate for missing root nodes
        root = std::make_shared<ModuleNode>();
        this->registeredModules[currPath] = root;
    }

    do {
        currPath = path.front();
        path.erase(path.begin());

        auto moduleNode = ModuleNode::findNode(root->treeRef(), currPath);
        if (moduleNode == nullptr) {
            auto sub = std::make_shared<ModuleNode>();
            root->add(currPath, sub);
            root = sub;
        } else {
            root = moduleNode;
        }
    } while (path.size() > 0);
    return root;
}

// Access operators
// operator[] forwards to a single method.
std::shared_ptr<ModuleNode> ModuleTree::operator[](const std::string& input) {
    return ModuleNode::findNode(this->registeredModules, input);
}

std::shared_ptr<ModuleNode> ModuleNode::operator[](const std::string& input) {
    return ModuleNode::findNode(this->children, input);
}

auto ModuleNode::get(const std::string& input) -> std::shared_ptr<ModuleNode> {
    return (*this)[input];
}

} // namespace nova
