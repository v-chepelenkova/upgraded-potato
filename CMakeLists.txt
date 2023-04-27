cmake_minimum_required(VERSION 3.12)
project(Metasimulator)

# Tell where the CORE folder with abstract classes is
set(INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/CORE
                        ${PROJECT_SOURCE_DIR}/external)

# Subdirectory with some simulator
add_subdirectory(CORE)
add_subdirectory("Storage_(example)")
add_subdirectory("solar_system")