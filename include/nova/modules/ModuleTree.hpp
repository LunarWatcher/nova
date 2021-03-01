#pragma once

#include "Module.hpp"
#include <iostream>
#include <map>
#include <memory>
#include <variant>

namespace nova {

class ModuleNode;

typedef std::map<std::string, std::variant<std::string, std::shared_ptr<ModuleNode>>> ModuleTreeMap;

/**
 * Tree node element.
 *
 * This is a helper class for {@link ModuleTree}, and shouldn't be used
 * on its own.
 */
class ModuleNode {
private:
    /**
     * Internal: contains the node mapping
     */
    ModuleTreeMap children;

public:
    /**
     * The module for this node of the tree.
     * Note that if this node is null at runtime,
     * this entire branch will be disregarded and remain in
     * an unusable state.
     *
     * Handling and notifying the user will be handled by the system,
     * so while no direct action is required by external modules, it's
     * always a good idea to explicitly state if there are any other
     * dependencies that need to be added. If that's the case,
     * notifying the user gives them the opportunity to find and
     * install the proper binaries.
     */
    std::shared_ptr<Module> module;

    bool add(const std::string& k, std::shared_ptr<ModuleNode> node);
    bool add(const std::string& k, const std::string& alias);

    static std::shared_ptr<ModuleNode> findNode(ModuleTreeMap& haystack, const std::string& key);
    std::shared_ptr<ModuleNode> operator[](const std::string& input);
    std::shared_ptr<ModuleNode> get(const std::string& input);
    ModuleTreeMap& treeRef() {
        return this->children;
    }
};

/**
 * This is essentially a wrapper around std::map, but with a tree specialization.
 * Its access has been heavily restricted as well, largely to prevent issues
 * with bad access that could potentially break Nova.
 */
class ModuleTree {
private:
    inline static std::shared_ptr<ModuleTree> INSTANCE = nullptr;

    ModuleTreeMap registeredModules;
    std::shared_ptr<ModuleNode> resolvePath(std::vector<std::string> path);

public:
    void registerModule(std::shared_ptr<Module> module, const std::vector<std::string>& path = {});
    bool registerAlias(const std::string& target, const std::string& alias, const std::vector<std::string>& path = {});

    /**
     * @param moduleName    The module to get
     * @return              The module for the associated name, or nullptr if not found
     */
    std::shared_ptr<Module> getModule(const std::string& moduleName, const std::vector<std::string>& path = {});
    static std::shared_ptr<ModuleTree> getInstance();

    std::shared_ptr<ModuleNode> operator[](const std::string& input);
};

} // namespace nova
