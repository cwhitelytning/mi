# Minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Project name and version
project(mi
        VERSION 1.0.0
        DESCRIPTION "Modular Interface"
        LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Author of the project
set(PROJECT_AUTHOR "Clay Whitelytning")

# Find all .cpp files in the src directory to compile
file(GLOB MI_SOURCE_FILES "src/*.cpp")

# Define the executable to be built from the source files
add_library(${PROJECT_NAME} STATIC ${MI_SOURCE_FILES})

# Add compile definitions to store various project details
target_compile_definitions(${PROJECT_NAME} PRIVATE
        MI_PROJECT_HASH="${GIT_HASH}"
        MI_PROJECT_NAME="${PROJECT_NAME}"
        MI_PROJECT_AUTHOR="${PROJECT_AUTHOR}"
        MI_PROJECT_VERSION="${PROJECT_VERSION}"
        MI_PROJECT_VERSION_MAJOR="${PROJECT_VERSION_MAJOR}"
        MI_PROJECT_VERSION_MINOR="${PROJECT_VERSION_MINOR}"
        MI_PROJECT_VERSION_PATCH="${PROJECT_VERSION_PATCH}"
        MI_PROJECT_DESCRIPTION="${PROJECT_DESCRIPTION}"
)

# Include directories for header files
target_include_directories(${PROJECT_NAME} PUBLIC inc)
