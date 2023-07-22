inc_components = include_directories('.')
inc_dirs = [
  inc_components,
]

src_files = files([
  'Folderwatcher.cpp',
])

#dep_poco = dependency('poco', static: true)

deps_internal = []
deps_external = []

cxxflags_common = []
LDFlags = []

FolderWatcher = executable(
  'FolderWatcher',
  sources: src_files,
  link_args: LDFlags,
  cpp_args: cxxflags_common,
  include_directories: inc_dirs,
  gnu_symbol_visibility: 'hidden',
  link_with: deps_internal,
  dependencies: deps_external,
  install: true
  )