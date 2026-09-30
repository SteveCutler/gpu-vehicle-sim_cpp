cmake_minimum_required(VERSION 3.16)
project(gpu_vehicle_sim LANGUAGES CXX)

option(ENABLE_RENDERER "Build the SFML renderer" ON)

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

if(ENABLE_RENDERER)
    find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)
    target_sources(vehicle_sim PRIVATE src/renderer.cpp)
    target_link_libraries(vehicle_sim PRIVATE SFML::Graphics SFML::Window SFML::System)
    target_compile_definitions(vehicle_sim PRIVATE ENABLE_RENDERER)
endif()