dpa_sdk = get_option('doca_sdk_path')

dpa_inc = include_directories(dpa_sdk + '/include')

dpa_lib = static_library('http_parser_dpa',
    'http_parser_dpa.c',
    include_directories : dpa_inc,
    install : false)
