cmake_minimum_required(VERSION 3.10)
project(Metasimulator)

#message("top PROJECT_SOURCE_DIR = " ${PROJECT_SOURCE_DIR})
#message("subdir = " "Storage_\(example\)")
#message("PROJECT_NAME = " ${PROJECT_NAME})

# Tell where the CORE folder with abstract classes is
set(INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/CORE)

#message("INCLUDE_DIRECTORIES = " ${INCLUDE_DIRECTORIES})

# Subdirectory with some simulator
add_subdirectory("Storage_(example)")
#add_subdirectory("Solar_System")