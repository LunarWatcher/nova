#include "nova/modules/ModuleTree.hpp"
#include "catch2/catch_test_macros.hpp"
#include "nova/modules/Module.hpp"
#include "nova/modules/builtins/HelpModule.hpp"
#include <memory>

TEST_CASE("Basic tree functionality", "[TreeFunctioning]") {
    nova::ModuleTree tree;
    auto module = std::make_shared<nova::HelpModule>();

    SECTION("Base access rule: non-existing keys return null") {
        REQUIRE(tree.getModule("Arbitrary null crap") == nullptr);
    }

    SECTION("Top-level modules should behave") {
        tree.registerModule(module);
        REQUIRE(tree.getModule("help") != nullptr);
        REQUIRE(tree["help"] != nullptr);
        REQUIRE(tree["help2"] == nullptr);
        REQUIRE(tree.registerAlias("help", "help2"));
        REQUIRE(tree["help2"] != nullptr);
        REQUIRE(tree["help2"]->module != nullptr);
        REQUIRE(tree["help2"]->module->getName() == "help");
    }

    SECTION("UNLIMITED RECURSION! Is horrible, that is.") {
        tree.registerModule(module);
        REQUIRE(tree.getModule("help") != nullptr);
        REQUIRE(tree.registerAlias("help", "me"));
        REQUIRE(tree["me"] != nullptr);
        REQUIRE(tree.registerAlias("me", "you"));
        REQUIRE(tree["you"] == nullptr);
        REQUIRE(tree.registerAlias("me", "help") == false);
        REQUIRE(tree["help"] != nullptr);
        REQUIRE(tree["help"]->module->getName() == "help");
    }
    SECTION("Check deep nesting") {
        tree.registerModule(module, {"never", "gonna", "give", "you", "up"});
        REQUIRE(tree["never"] != nullptr);
        REQUIRE(tree["never"]->get("gonna") != nullptr);
        REQUIRE(tree["never"]->get("gonna")->get("give") != nullptr);
        REQUIRE(tree["never"]->get("gonna")->get("give")->get("you") != nullptr);
        auto node = tree["never"]->get("gonna")->get("give")->get("you")->get("up");
        REQUIRE(node != nullptr);
        REQUIRE(node->get("help") != nullptr);
        // at this point, we've shown more than enough times that this is fine.
        REQUIRE(node->get("help")->module->getName() == "help");
    }
}

TEST_CASE("Test tree add surrender", "[TreeSurrender]") {
    nova::ModuleTree tree;
    REQUIRE(tree["oogaabooga"] == nullptr);
    REQUIRE(tree.registerAlias("help", "yourself"));
    auto module = std::make_shared<nova::HelpModule>();
    tree.registerModule(module);
    REQUIRE(tree.registerAlias("help", "yourself") == false);
    REQUIRE(tree["help"] != nullptr);
    REQUIRE(tree["help"]->module != nullptr);
    REQUIRE(tree["help"]->module->getName() == "help");
}
