project("EventSystem")

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
include_directories(${PROJECT_NAME} PRIVATE ${UTILITY_INCLUDE_DIR})

# add to lib
add_library(${PROJECT_NAME} STATIC ${HEADERS_SOURCES})

# Enbale/ Disable PCH compiling
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.16 AND EVENT_SYSTEM_BUILD_USING_PCH)
    message(STATUS "EventSystem - ENABLED pre-compiled header support.")
    target_precompile_headers(${PROJECT_NAME} PUBLIC ${HEADERS})
    set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)
else()
    message(STATUS "EventSystem - DISABLED pre-compiled header support.")
endif()

# lib HEADERs
target_include_directories(${PROJECT_NAME} PRIVATE ${UTILITY_INCLUDE_DIR})

