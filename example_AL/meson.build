project('example_AL', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3'])

incdir = include_directories(['../AdsAL/AdsClient', '../AdsAL/AdsCommon',
  '../AdsLib', '../AdsLib/standalone'])

exe = executable('example_al', 'example.cpp',
  include_directories: incdir,
  install : true)

test('basic', exe)
