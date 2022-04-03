project("Utility")

file(GLOB HEADERS_SOURCES
    *.h
    *.hpp
    *.cc
    *.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS_SOURCES})


