project("Application")

file(GLOB SOURCES
    *.h
    *.hpp
    *.cc
    *.cpp
)

# make the single executable
add_executable(${PROJECT_NAME} ${SOURCES})

# lib HEADERs
target_include_directories(${PROJECT_NAME} PRIVATE ${UTILITY_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${EVENT_SYSTEM_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${FILE_SERVICE_INCLUDE_DIR})

# for linking libs
target_link_libraries(${PROJECT_NAME} PRIVATE ${UTILITY_PRO})
target_link_libraries(${PROJECT_NAME} PRIVATE ${EVENT_SYSTEM_PRO})
target_link_libraries(${PROJECT_NAME} PRIVATE ${FILE_SERVICE_PRO})
