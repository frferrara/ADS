project(
  'example_AL', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3']
)

exe_files = files(['example.cpp'])
lib_files = files(['../AdsAL/AdsClient/TcAdsClientWrapper.cpp'])

incdir = include_directories([
  '../AdsAL/AdsClient',
  '../AdsAL/AdsCommon'
])

adslib_dep = subproject('AdsLib').get_variable('adslib_dep')

exe = executable(
  'example_al', [exe_files, lib_files],
  include_directories: incdir,
  dependencies: adslib_dep,
  install : true
)

test('basic', exe)
