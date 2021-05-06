cmake_minimum_required(VERSION 3.0.0)
project(Practica1 VERSION 0.1.0)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "../bin")

include(CTest)
enable_testing()

find_package( OpenCV REQUIRED )
find_package( Threads REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(Practica1 "source_files/main.cpp")

target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
