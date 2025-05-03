cmake_minimum_required(VERSION 3.10)
project(OpenGLProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(include)


# Add source files
set(SOURCES
    src/main.cpp
    src/glad.c
    src/Shader.cpp
    src/Circle.cpp
    src/Application.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME}
    OpenGL::GL
    glfw
    ${CMAKE_DL_LIBS}  # For dynamic loading (needed by GLAD)
)
