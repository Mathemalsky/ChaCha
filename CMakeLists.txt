cmake_minimum_required(VERSION 3.10)

# project name is defined here
project(chacha)

# not build in CI by default
OPTION(CIBuild "Configuration for build in CI" OFF)

message(STATUS "CIBuild=${CIBuild}")

# specify where the output should be compiled
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)

# set the compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3 -pthread -Wall -Wextra -pedantic -g -funroll-loops")
if(${CIBuild} STREQUAL OFF)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
endif()

# lists all sourcefiles to be compiled with the project
file(GLOB SOURCES "src/*.cpp")

#lists all header files to be included in the project
file(GLOB HEADERS "include/*.hpp")

# print useful info about compiler setting
message(STATUS "Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

#add all sourcefiles and headerfiles to the project
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# look for included files also in the following directories
target_include_directories(${PROJECT_NAME} PUBLIC include)


# link the csprng library to project
# standard library needs to be additionally linked in windows
if(WIN32)
  target_link_libraries(${PROJECT_NAME} stdc++)
endif()

# on windows pack the needed dlls in the output directory
if(WIN32 AND ${CIBuild} STREQUAL ON)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "C:/msys64/mingw64/bin/libstdc++-6.dll" ${CMAKE_HOME_DIRECTORY}/bin
    COMMAND ${CMAKE_COMMAND} -E copy "C:/msys64/mingw64/bin/libwinpthread-1.dll" ${CMAKE_HOME_DIRECTORY}/bin
    COMMAND ${CMAKE_COMMAND} -E copy "C:/msys64/mingw64/bin/libgcc_s_seh-1.dll" ${CMAKE_HOME_DIRECTORY}/bin
    )
endif()

