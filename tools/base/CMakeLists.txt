aux_source_directory(src SOURCES)

add_library(base STATIC ${SOURCES})

target_include_directories(base
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)