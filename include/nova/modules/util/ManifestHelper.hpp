#pragma once

#include <memory>

#include "nlohmann/json.hpp"

namespace nova {

class ManifestHelper {
private:
    std::shared_ptr<ManifestHelper> INSTANCE;
    std::map<std::string, nlohmann::json> moduleManifests;

public:
    std::shared_ptr<ManifestHelper> getInstance();
};

} // namespace nova
