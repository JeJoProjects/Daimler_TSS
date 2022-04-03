project("Application")

add_subdirectory(1_Utility)
set(UTILITY_PRO  "Utility")


add_subdirectory(2_EventSystem)
set(EVENT_SYSTEM_PRO  "EventSystem")

add_subdirectory(3_FileService)
set(FILE_SERVICE_PRO  "FileService")


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
