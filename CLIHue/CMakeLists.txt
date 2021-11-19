cmake_minimum_required(VERSION 3.21.3)
project(CLIHue)

add_executable(testlights testlights.cpp)

set_property(TARGET testlights PROPERTY CXX_STANDARD 14)
set_property(TARGET testlights PROPERTY CXX_EXTENSIONS OFF)
target_link_libraries(testlights hueplusplusstatic)

add_executable(ControllLights ControllLights.cpp)

set_property(TARGET ControllLights PROPERTY CXX_STANDARD 14)
set_property(TARGET ControllLights PROPERTY CXX_EXTENSIONS OFF)
target_link_libraries(ControllLights hueplusplusstatic)
