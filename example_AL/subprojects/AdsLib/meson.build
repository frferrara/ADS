project('AdsLib', 'cpp')

cpp = meson.get_compiler('cpp')
libs = [
  cpp.find_library('AdsLib', dirs : meson.current_source_dir()),
  cpp.find_library('ws2_32', required: false),
  dependency('threads'),
]
adslib_dep = declare_dependency(
  dependencies: libs,
  include_directories : include_directories('include')
)
