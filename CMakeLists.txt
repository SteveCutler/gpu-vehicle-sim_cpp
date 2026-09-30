cmake_minimum_required(VERSION 3.16)
project(gpu_vehicle_sim LANGUAGES CXX)

add_executable(vehicle_sim
    src/main.cpp
    src/vehicleBatch.cpp
    src/environment.cpp
    src/dynamics.cpp
    src/controller.cpp
    src/renderer.cpp
)

target_include_directories(vehicle_sim PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(vehicle_sim PRIVATE cxx_std_17)