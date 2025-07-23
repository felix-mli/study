
aux_source_directory(src SOURCES)

add_library(my_math
    STATIC
    ${SOURCES}
)

target_include_directories(my_math
    PUBLIC
    ${CMAKE_SOURCE_DIR}/3rdparty/googletest-1.17.0/googletest/include
)

add_executable(my_math_gtest
    main.cpp
    ${SOURCES}
)

target_link_libraries(my_math_gtest
    my_math
    gtest
    gtest_main
    pthread
)

