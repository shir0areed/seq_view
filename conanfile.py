from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps

class Recipe(ConanFile):
    settings = 'os', 'compiler', 'build_type', 'arch'
        
    options = {
        'build_test': [True, False],
    }
    default_options = {
        'build_test': False,
    }

    def requirements(self):
        pass

    def build_requirements(self):
        self.tool_requires('cmake/[^3.23]')
        
    def generate(self):
        tc = CMakeToolchain(self)
        tc.user_presets_path = False
        tc.variables['CMAKE_POLICY_DEFAULT_CMP0091']='NEW'
        tc.variables['SEQVIEW_BUILD_TEST'] = bool(self.options.build_test)
        tc.generate()

        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
