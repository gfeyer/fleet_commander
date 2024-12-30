cmake_minimum_required(VERSION 3.28)
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

# Define the executable
file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(FleetDominion ${SOURCES})

# Link libraries to the executable
target_link_libraries(FleetDominion PRIVATE 
    sfml-system 
    sfml-window 
    sfml-graphics 
    sfml-audio 
    TGUI::TGUI
)

# Find behaviortree_cpp
find_package(behaviortree_cpp CONFIG REQUIRED)
target_link_libraries(FleetDominion PRIVATE BT::behaviortree_cpp)

# Set the C++ standard
target_compile_features(FleetDominion PRIVATE cxx_std_20)

add_custom_command(
    TARGET FleetDominion POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:FleetDominion>/assets
)

# Copy Behavior Tree XML files to the output directory
file(GLOB BEHAVIOR_TREE_FILES 
    ${CMAKE_SOURCE_DIR}/src/Game/AI/BehaviorTrees/*.xml
)
foreach(xml_file ${BEHAVIOR_TREE_FILES})
    get_filename_component(xml_filename ${xml_file} NAME)
    add_custom_command(
        TARGET FleetDominion POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${xml_file}
        $<TARGET_FILE_DIR:FleetDominion>/${xml_filename}
        COMMAND ${CMAKE_COMMAND} -E echo "Copied ${xml_filename} to $<TARGET_FILE_DIR:FleetDominion>"
    )
endforeach()
