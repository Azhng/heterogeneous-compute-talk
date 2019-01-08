file(GLOB kernels kernels/*.cl)
file(COPY ${kernels}
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../kernels/)
include_directories(${OpenCL_INCLUDE_DIRS})

add_executable(demo main.c)
add_executable(add_gpu add_gpu.cpp)
add_executable(add_cpu add_cpu.cpp)

target_link_libraries(demo ${OpenCL_LIBRARY})
target_link_libraries(add_gpu ${OpenCL_LIBRARY})
