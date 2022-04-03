project("FileService")

file(GLOB HEADERS
    *.h
    *.hpp
)

file(GLOB HEADERS_SOURCES
    *.h
    *.hpp
    *.cc
    *.cpp
)

# add to lib
add_library(${PROJECT_NAME} STATIC ${HEADERS_SOURCES})

# Enbale/ Disable PCH compiling
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.16 AND BUILD_USING_PCH)
    message(STATUS "FileService - ENABLED pre-compiled header support.")
    target_precompile_headers(${PROJECT_NAME} PUBLIC ${HEADERS})
    set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)
else()
    message(STATUS "FileService - DISABLED pre-compiled header support.")
endif()

# third party lib headers
# target_include_directories)


# lib HEADERs
target_include_directories(${PROJECT_NAME} PRIVATE ${UTILITY_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${EVENT_SYSTEM_INCLUDE_DIR})




