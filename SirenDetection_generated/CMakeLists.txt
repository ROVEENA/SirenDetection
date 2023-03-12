cmake_minimum_required(VERSION 3.14)

project(SirenDetection
        DESCRIPTION "Functions for siren detection"
        LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(AlertDecision)
add_subdirectory(Common)
add_subdirectory(data)
add_subdirectory(IdentifyEV)
add_subdirectory(Preprocessing)
add_subdirectory(VehicleMode)
