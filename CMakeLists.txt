cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

# Set the output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Option to build shared libraries
# option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Find SFML components
find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)

# Define the executable
file(GLOB SOURCES src/*.cpp)
add_executable(main ${SOURCES})

# Link libraries to the executable
target_link_libraries(main PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)

# Copy the res folder to the bin directory after building
# add_custom_command(
#     TARGET main POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#     ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:main>/res
# )

# Set the C++ standard required
target_compile_features(main PRIVATE cxx_std_17)
