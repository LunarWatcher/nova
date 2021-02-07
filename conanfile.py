from conans import ConanFile, CMake, tools


class NovaConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "scons"
    default_options = {}

    def requirements(self):
        self.requires("nlohmann_json/3.9.1")
