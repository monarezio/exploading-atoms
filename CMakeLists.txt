cmake_minimum_required(VERSION 3.10)
project(exploading_atoms)

set(CMAKE_CXX_STANDARD 11)

add_definitions("-std=c++11")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK3 REQUIRED gtk+-3.0)

include_directories (${GTK3_INCLUDE_DIRS})
link_directories (${GTK3_LIBRARY_DIRS})
add_executable(exploading_atoms src/main.cpp src/domain/ExploadingAtoms.cpp src/domain/ExploadingAtoms.h src/domain/models/Player.h src/domain/models/Field.cpp src/domain/models/Field.h src/domain/models/Coordinate.cpp src/domain/models/Coordinate.h src/domain/ai/Ai.h src/domain/ai/Minimax.cpp src/domain/ai/Minimax.h)
add_definitions (${GTK3_CFLAGS_OTHER})
target_link_libraries (exploading_atoms ${GTK3_LIBRARIES})
target_link_libraries(exploading_atoms ${CONAN_LIBS})