#include "nova/loading/ModLoader.hpp"
#include <iostream>
#include <memory>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include <stdio.h>

namespace nova {

typedef void (*novamain_t)();

ModLoader::~ModLoader() {
    for (auto& ptr : libs) {
#ifdef _WIN32
        FreeLibrary((HMODULE) ptr);
#else
        dlclose(ptr);
#endif
    }
}

void ModLoader::loadDynamicLibrary(const std::string& path) {
#ifdef _WIN32
    void* dhl = LoadLibrary(path.c_str());
#else
    void* dhl = dlopen(path.c_str(), RTLD_LAZY);
#endif

    if (dhl == nullptr) {
        throw std::string("[DYLoad] Critical error: failed to load " + path
#ifndef _WIN32
                          + ": " + std::string(dlerror())
#endif
        );
    }
    this->libs.push_back(dhl);

#ifdef _WIN32
    // An HMODULE is a void*, but the Windows API being absolute garbage prevents
    // an implicit cast from void* to a type that's void* :facepaw:
    // Fuck you Windows
    novamain_t nmain = (novamain_t) GetProcAddress((HMODULE) dhl, "NovaMain");
    if (nmain == nullptr) {
        throw std::string("Failed to locate NovaMain");
    }
#else
    dlerror();

    novamain_t nmain = (novamain_t) dlsym(dhl, "NovaMain");
    const auto err = dlerror();
    if (err) {
        throw std::string(err);
    }
#endif
    nmain();
}

std::shared_ptr<ModLoader> ModLoader::getInstance() {
    if (ModLoader::INSTANCE == nullptr) {
        ModLoader::INSTANCE = std::make_shared<ModLoader>();
    }

    return ModLoader::INSTANCE;
}

} // namespace nova
