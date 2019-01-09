cmake_minimum_required(VERSION 3.13)

project(QtIrbis)
 
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_PREFIX_PATH "C:/Qt/5.11.2/msvc2017_64")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_compile_definitions(QTIRBIS_LIBRARY)
 
find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)

FILE(GLOB HFiles *.h) 
FILE(GLOB CppFiles *.cpp)

set(SOURCES ${CppFiles} ${HFiles}) 
 
add_library(QtIrbis SHARED ${SOURCES} ${HEADERS} ${UI})
target_link_libraries(QtIrbis Qt5::Core Qt5::Network)
