project("FileService")


file(GLOB HEADERS_SOURCES
    *.h
    *.hpp
    *.cc
    *.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS_SOURCES})

# third party lib headers
# target_include_directories)


# lib HEADERs
target_include_directories(${PROJECT_NAME} PRIVATE ${UTILITY_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${EVENT_SYSTEM_INCLUDE_DIR})




