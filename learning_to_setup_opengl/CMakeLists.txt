cmake_minimum_required(VERSION 3.10)

# Set the cross-compiling toolchain before the project declaration
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)

project(OpenGLProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
# For Windows, we need to manually specify paths
set(GLFW_INCLUDE_DIR /usr/x86_64-w64-mingw32/include)
set(GLFW_LIBRARY /usr/x86_64-w64-mingw32/lib/libglfw3.a)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(include)
include_directories(${GLFW_INCLUDE_DIR})

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
    ${GLFW_LIBRARY}
    -lopengl32
    -lgdi32
    ${CMAKE_DL_LIBS}
)

# Add .exe extension for Windows
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".exe")
# --------------------

# cmake_minimum_required(VERSION 3.10)
# project(OpenGLProject)
#
# # Set C++ standard
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
#
# # Find required packages
# find_package(OpenGL REQUIRED)
# find_package(glfw3 REQUIRED)
#
# # Include directories
# include_directories(${PROJECT_SOURCE_DIR}/include)
# include_directories(include)
#
#
# # Add source files
# set(SOURCES
#     src/main.cpp
#     src/glad.c
#     src/Shader.cpp
#     src/Circle.cpp
#     src/Application.cpp
# )
#
# # Create executable
# add_executable(${PROJECT_NAME} ${SOURCES})
#
# # Link libraries
# target_link_libraries(${PROJECT_NAME}
#     OpenGL::GL
#     glfw
#     ${CMAKE_DL_LIBS}  # For dynamic loading (needed by GLAD)
# )
