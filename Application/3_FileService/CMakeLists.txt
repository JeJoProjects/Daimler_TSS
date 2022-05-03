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

# lib HEADERs
include_directories(${PROJECT_NAME} PRIVATE
    ${UTILITY_INCLUDE_DIR}
    ${EVENT_SYSTEM_INCLUDE_DIR}
)

# add to lib
add_library(${PROJECT_NAME} STATIC ${HEADERS_SOURCES})

# Enbale/ Disable PCH compiling
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.16 AND FILE_SERVICE_BUILD_USING_PCH)
    message(STATUS "FileService - ENABLED pre-compiled header support.")
    target_precompile_headers(${PROJECT_NAME} PUBLIC ${HEADERS})
    set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)
else()
    message(STATUS "FileService - DISABLED pre-compiled header support.")
endif()

# lib HEADERs
target_include_directories(${PROJECT_NAME} PRIVATE
    ${UTILITY_INCLUDE_DIR}
    ${EVENT_SYSTEM_INCLUDE_DIR}
)




