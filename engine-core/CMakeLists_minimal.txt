cmake_minimum_required(VERSION 3.20)
project(YUGAEngineMinimal VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Minimal source files - Just Math Library
set(SOURCES
    # Math
    src/Math/Vector2.cpp
    src/Math/Vector4.cpp
    src/Math/Matrix4.cpp
    src/Math/Quaternion.cpp
    src/Math/Transform.cpp
    
    # Main
    src/main_minimal.cpp
)

# Create executable
add_executable(YUGAEngineMinimal ${SOURCES})

# Include directories
target_include_directories(YUGAEngineMinimal PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Set output directory
set_target_properties(YUGAEngineMinimal PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
