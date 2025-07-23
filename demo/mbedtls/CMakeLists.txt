add_executable(mbedtls_demo
    mbedtls_demo.c
)
target_include_directories(mbedtls_demo
    PUBLIC ${CMAKE_SOURCE_DIR}/3rdparty/mbedtls-mbedtls-3.6.3/include
)
target_link_libraries(mbedtls_demo
    PUBLIC 
    mbedtls
    mbedcrypto
    mbedx509
    base
)