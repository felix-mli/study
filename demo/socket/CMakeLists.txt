add_executable(server
    server/server.c
)
target_link_libraries(server
    PRIVATE base
)

add_executable(client
    client/client.c
)
target_link_libraries(client
    PRIVATE base
)