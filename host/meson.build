dpa_sdk = get_option('doca_sdk_path')

doca_deps = [
    dependency('doca-flow', required : true),
    dependency('doca-dpa', required : true),
    dependency('doca-log', required : true)
]

dpa_inc = include_directories(dpa_sdk + '/include')

executable('doca_http_parser',
    'main.cpp',
    include_directories : dpa_inc,
    link_with : dpa_lib,
    dependencies : doca_deps)
