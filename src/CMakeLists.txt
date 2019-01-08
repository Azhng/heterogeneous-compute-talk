file(GLOB kernels kernels/*.cl)
file(COPY ${kernels}
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../kernels/)
include_directories(${OpenCL_INCLUDE_DIRS})

add_executable(add_gpu add_gpu.cpp)
add_executable(add_cpu add_cpu.cpp)
add_executable(hello hello.cpp)

target_link_libraries(add_gpu ${OpenCL_LIBRARY})
target_link_libraries(hello ${OpenCL_LIBRARY})
