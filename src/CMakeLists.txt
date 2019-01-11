file(GLOB kernels kernels/*.cl)
file(GLOB resources resources/*)

file(COPY ${resources}
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../resources/)
file(COPY ${kernels}
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../kernels/)

include_directories(${OpenCL_INCLUDE_DIRS})

add_executable(add_gpu add_gpu.cpp)
add_executable(add_cpu add_cpu.cpp)
add_executable(rotate_cpu rotate_cpu.cpp)
add_executable(rotate_gpu rotate_gpu.cpp)
add_executable(hello hello.cpp)

target_link_libraries(add_gpu ${OpenCL_LIBRARY})
target_link_libraries(hello ${OpenCL_LIBRARY})
target_link_libraries(rotate_cpu m)
target_link_libraries(rotate_gpu ${OpenCL_LIBRARY})
target_link_libraries(rotate_gpu m)
