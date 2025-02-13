cmake_minimum_required(VERSION 3.24)
project(ColonySimulator LANGUAGES CXX)

# Set output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Specify the source directory as an include path
include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

# Find SFML
find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)

# Find TGUI
find_package(TGUI CONFIG REQUIRED)

# message(STATUS "TGUI Found: ${TGUI_FOUND}")
# message(STATUS "TGUI Include Dir: ${TGUI_INCLUDE_DIR}")

# Define the executable
file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(FleetCommander ${SOURCES})

# Link libraries to the executable
target_link_libraries(FleetCommander PRIVATE 
    sfml-system 
    sfml-window 
    sfml-graphics 
#    sfml-audio 
    TGUI::TGUI
)

# Set the C++ standard
target_compile_features(FleetCommander PRIVATE cxx_std_17)

add_custom_command(
    TARGET FleetCommander POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:FleetCommander>/assets
)
