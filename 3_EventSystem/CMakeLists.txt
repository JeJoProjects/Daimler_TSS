project("EventSystem")

file(GLOB HEADERS_SOURCES
    *.h
    *.hpp
    *.cc
    *.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS_SOURCES})


# lib HEADERs
target_include_directories(${PROJECT_NAME} PRIVATE ${UTILITY_INCLUDE_DIR})

