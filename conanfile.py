from conan import ConanFile

class CGCPPRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "PremakeDeps"

    def requirements(self):
        # === SERVICE ===
        # General
        self.requires("fmt/10.2.1")
        self.requires("boost/1.86.0")
        self.requires("spdlog/1.14.1")
        self.requires("nlohmann_json/3.11.3")

        # WebServer
        self.requires("inja/3.4.0")
        self.requires("openssl/3.3.2")
        self.requires("cpp-httplib/0.18.0")

        # MachineInterface
        self.requires("libmodbus/3.1.10")

        # === TEST ===
        self.requires("gtest/1.15.0") 

    def configure(self):
        self.options["boost"].without_fiber = False
