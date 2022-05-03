project("Utility")


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
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.16 AND UTILITY_BUILD_USING_PCH)
    message(STATUS "Utility - ENABLED pre-compiled header support.")
    target_precompile_headers(${PROJECT_NAME} PUBLIC ${HEADERS})
    set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)
else()
    message(STATUS "Utility - DISABLED pre-compiled header support.")
endif()

