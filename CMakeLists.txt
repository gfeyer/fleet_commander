cmake_minimum_required(VERSION 3.28)
project(ColonySimulator LANGUAGES CXX)

# Set output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find SFML
find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)

# Find TGUI
find_package(TGUI CONFIG REQUIRED)

# message(STATUS "TGUI Found: ${TGUI_FOUND}")
# message(STATUS "TGUI Include Dir: ${TGUI_INCLUDE_DIR}")

# Define the executable
file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(main ${SOURCES})

# Link libraries to the executable
target_link_libraries(main PRIVATE 
    sfml-system 
    sfml-window 
    sfml-graphics 
    sfml-audio 
    TGUI::TGUI
)

# Set the C++ standard
target_compile_features(main PRIVATE cxx_std_17)

# Copy theme.txt to the binary directory after building
# add_custom_command(
#     TARGET main POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#     ${CMAKE_SOURCE_DIR}/theme.txt $<TARGET_FILE_DIR:main>
# )

# Copy other resources if needed
# add_custom_command(
#     TARGET main POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#     ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:main>/resources
# )

add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:main>/resources
)
