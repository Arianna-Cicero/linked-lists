cmake_minimum_required(VERSION 3.27)
project(linked_lists C)

set(CMAKE_C_STANDARD 11)

# Add the source files to the project
add_executable(linked_lists
        main.c
        matriz_lista_ligada.c
        linha_lista_ligada.c
        no_lista_ligada.c
)

# Include the header files directory
target_include_directories(linked_lists PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link the math library
target_link_libraries(linked_lists m)