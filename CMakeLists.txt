cmake_minimum_required(VERSION 3.12)
project(Metasimulator)

#message("top PROJECT_SOURCE_DIR = " ${PROJECT_SOURCE_DIR})
#message("subdir = " "Storage_\(example\)")
#message("PROJECT_NAME = " ${PROJECT_NAME})

# Tell where the CORE folder with abstract classes is
set(INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/CORE)

#message("INCLUDE_DIRECTORIES = " ${INCLUDE_DIRECTORIES})

# Subdirectory with some simulator
add_subdirectory(EngineCore)
add_subdirectory("Storage_(example)")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Application)
