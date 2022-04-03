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
add_subdirectory(ThirdParty)
set(LINDENB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty)
set(UTILITY_INCLUDE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/Application/1_Utility)
set(EVENT_SYSTEM_INCLUDE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/Application/2_EventSystem)
set(FILE_SERVICE_INCLUDE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/Application/3_FileService)

add_subdirectory(Application)
set(APPLICATION_PRO  "Application")

# set start project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
       PROPERTY VS_STARTUP_PROJECT ${APPLICATION_PRO})
