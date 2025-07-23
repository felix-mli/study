aux_source_directory(src SOURCES)

add_executable(cjson_demo
    main.c
    ${SOURCES}
)

target_include_directories(cjson_demo
    PUBLIC
    ${CMAKE_SOURCE_DIR}/3rdparty/cJSON-1.7.18
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(cjson_demo
    cjson
    base
)