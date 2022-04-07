cmake_minimum_required(VERSION 3.23)

# sln name
project("DTSS_Task")

# separate projects
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

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

# set start project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
       PROPERTY VS_STARTUP_PROJECT ${APPLICATION_PRO})
