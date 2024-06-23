from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps

class Recipe(ConanFile):
    settings = 'os', 'compiler', 'build_type', 'arch'

    def requirements(self):
        pass

    def build_requirements(self):
        self.tool_requires('cmake/[^3.23]')
        
    def generate(self):
        tc = CMakeToolchain(self)
        tc.user_presets_path = False
        tc.variables['CMAKE_POLICY_DEFAULT_CMP0091']='NEW'
        tc.generate()

        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()