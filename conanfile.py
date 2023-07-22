from conans import ConanFile, tools, Meson
import os

class FolderWatcher(ConanFile):
    name = 'FolderWatcher'
    url = '...'
    generators = "pkg_config"
    version = '1.0.0'
    remote = 'https://center.conan.io'
    description = 'App for tracking folder usage'
    settings = "os", "compiler", "build_type", "arch"

    #conan create . --profile ./Profiles/windowsc --build=missing
    
    _source_subfolder = name
    exports_sources = [_source_subfolder + '/*']

    options = {
        'enable_tests' : [True, False],     #Build and publish unit tests. Run if not cross build.
        'run_tests': [True, False]          #Run unit-tests in build process.
    }
    default_options = {
        'enable_tests' : True,
        'run_tests': False
    }

    def requirements(self):
        self.requires('poco/1.12.4')

    def build(self):
        meson = Meson(self, backend=None, build_type=None)
        meson.configure(build_folder="build",source_folder="FolderWatcher")
        meson.build()

    #def package_info(self):
    #    self.cpp_info.libs = tools.collect_libs(self)