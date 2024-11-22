cmake_minimum_required(VERSION 3.15)
project(FinalProjExamples)

# Ensure C++17 is used
set(CMAKE_CXX_STANDARD 17)

# Copy the 'sample_data' directory into the build directory
file(COPY ${CMAKE_SOURCE_DIR}/sample_data/ DESTINATION ${CMAKE_BINARY_DIR}/sample_data/)

# Show compiler output and enable warnings
set(CMAKE_VERBOSE_MAKEFILE ON)

# Conditionally add compile options based on the compiler
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # Visual Studio specific warnings
    add_compile_options(/W4)  # Use /W4 for MSVC to enable common warnings
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # GCC/Clang specific warnings
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Define executables
add_executable(rapidJSONExample rapidJSONExample.cpp)
add_executable(supersearch main.cpp DocumentParser.cpp IndexHandler.cpp porter2_stemmer.cpp QueryProcessor.cpp SearchEngine.cpp)

# If your main program (supersearch) uses the AVL tree, add the include directory
target_include_directories(supersearch PRIVATE ${CMAKE_SOURCE_DIR}/path/to/AVLTree)

# Link rapidjson to the project
target_include_directories(rapidJSONExample PRIVATE rapidjson/)

# Turn off verbose makefile after configuration
set(CMAKE_VERBOSE_MAKEFILE OFF)
