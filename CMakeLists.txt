# CMake configuration for demo project
cmake_minimum_required(VERSION 3.23)

# sln name
project("DTSS_Task")

# separate projects
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enbale/ Disable PCH compiling
option(BUILD_USING_PCH "Building using pre-compile support" ON)

# Sub folder CMakeLists
add_subdirectory(5_ThirdParty)
set(LINDENB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/5_ThirdParty)

add_subdirectory(2_Utility)
set(UTILITY_PRO  "Utility")
set(UTILITY_INCLUDE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/2_Utility)


add_subdirectory(3_EventSystem)
set(EVENT_SYSTEM_PRO  "EventSystem")
set(EVENT_SYSTEM_INCLUDE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/3_EventSystem)

add_subdirectory(4_FileService)
set(FILE_SERVICE_PRO  "FileService")
set(FILE_SERVICE_INCLUDE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/4_FileService)

add_subdirectory(1_Application)
set(APPLICATION_PRO  "Application")

# set start project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
       PROPERTY VS_STARTUP_PROJECT ${APPLICATION_PRO})
