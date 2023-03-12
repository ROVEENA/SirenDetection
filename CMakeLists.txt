cmake_minimum_required(VERSION 3.14)

project(siren_detection LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(include)

# Create a list with all .cpp source files
set( project_sources
   src/main.cpp
   src/AudioFFT.cpp
   src/utils.cpp
   src/calculation.cpp
   src/AudioFile.cpp
)

# Create executable with all necessary source files
add_executable(${PROJECT_NAME}
  ${project_sources}
)

