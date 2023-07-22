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
        self.requires('poco/1.9.4') #Poco version 1.9.4 becose problem with build libmysqlclient/8.0.31 

    def build(self):
        meson = Meson(self, backend=None, build_type=None)
        meson.configure(build_folder="build",source_folder="FolderWatcher")
        meson.build()

    def package(self):
        self.copy("F*.exe", "FolderWatcher", "build/FolderWatcher")
        self.copy("*.py", "FolderWatcher", "FolderWatcher/FolderWatcher")