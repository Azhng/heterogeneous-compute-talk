file(GLOB srcfiles *.c)
file(GLOB kernels kernels/*.cl)
file(COPY ${kernels}
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../kernels/)
include_directories(${OpenCL_INCLUDE_DIRS})

add_executable(demo ${srcfiles})
add_executable(democpp main.cpp)

target_link_libraries(demo ${OpenCL_LIBRARY})

target_link_libraries(democpp ${OpenCL_LIBRARY})
