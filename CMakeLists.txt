cmake_minimum_required(VERSION 3.20)

# sln name
project("DTSS_Task")

# set compiler and flags
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_BUILD_TYPE debug)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# multi process compiler
if(MSVC AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 19.12.25835)
       set(CMAKE_CXX20_STANDARD_COMPILE_OPTION "-std:c++latest")
       set(CMAKE_CXX20_EXTENSION_COMPILE_OPTION "-std:c++latest")
       set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /W4 /Zi /O2")

       message ("----------------------- MSVC compiler: " ${CMAKE_CXX_COMPILER_VERSION} " ------------------------")
       message ("------------- CXX Flags:" ${CMAKE_CXX_FLAGS} " -------------")
       message(STATUS "Architecture: ${ARCHITECTURE}")

#else("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND NOT CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 11.0)

       #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -O2 -Wall -Wextra") 

       #message ("----------------------- GCC compiler: " ${CMAKE_CXX_COMPILER_VERSION} " ------------------------")
       #message ("------------- CXX Flags:" ${CMAKE_CXX_FLAGS} " -------------")
endif()

# for adding google test
enable_testing()

# Enbale/ Disable PCH compiling
option(UTILITY_BUILD_USING_PCH "Utility: Building using pre-compile support" ON)
option(EVENT_SYSTEM_BUILD_USING_PCH "EventSystem: Building using pre-compile support" OFF)
option(FILE_SERVICE_BUILD_USING_PCH "FileService: Building using pre-compile support" OFF)


# Sub folder CMakeLists
add_subdirectory(ThirdParty)

set(gTEST_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/googletest)
set(UTILITY_INCLUDE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/Application/1_Utility)
set(EVENT_SYSTEM_INCLUDE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/Application/2_EventSystem)
set(FILE_SERVICE_INCLUDE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/Application/3_FileService)

add_subdirectory(Application)
set(APPLICATION_PRO  "Application")

add_subdirectory(AppGTest)


set_property(GLOBAL PROPERTY USE_FOLDERS ON)
file(GLOB_RECURSE APP_SRCS_LIST 
       RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/
       *.h
       *.hpp
       *.cc
       *.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${APP_SRCS_LIST})
# foreach(source IN LISTS APP_SRCS_LIST)
#     get_filename_component(source_path "${source}" PATH)
#     string(REPLACE "/" "\\" source_path_msvc "${source_path}")
#     source_group("${source_path_msvc}" FILES "${source}")
# endforeach()



# set start project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
       PROPERTY VS_STARTUP_PROJECT ${APPLICATION_PRO})
