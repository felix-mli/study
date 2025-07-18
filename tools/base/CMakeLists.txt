aux_source_directory(src SOURCE)

add_library(base STATIC ${SOURCE})

target_include_directories(base
    PUBLIC include
)