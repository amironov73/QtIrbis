cmake_minimum_required(VERSION 3.13)

project(OfflineTests)
 
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_PREFIX_PATH "C:/Qt/5.11.2/msvc2017_64")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

include_directories(../../Source/QtIrbis)
link_directories(../../Source/QtIrbis/cmake-build-debug)
 
find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Test REQUIRED)

FILE(GLOB HFiles *.h) 
FILE(GLOB CppFiles *.cpp)

set(SOURCES ${CppFiles} ${HFiles}) 
 
add_executable(OfflineTests ${SOURCES} ${HEADERS} ${UI})
target_link_libraries(OfflineTests Qt5::Core Qt5::Network Qt5::Test QtIrbis)
