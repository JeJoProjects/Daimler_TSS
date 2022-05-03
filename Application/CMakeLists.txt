project("Application")

add_subdirectory(1_Utility)
set(UTILITY_PRO  "Utility")


add_subdirectory(2_EventSystem)
set(EVENT_SYSTEM_PRO  "EventSystem")

add_subdirectory(3_FileService)
set(FILE_SERVICE_PRO  "FileService")


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
    ${FILE_SERVICE_INCLUDE_DIR}
)

# make the single executable
add_executable(${PROJECT_NAME} ${HEADERS_SOURCES})

# lib HEADERs
target_include_directories(${PROJECT_NAME} PRIVATE
    ${UTILITY_INCLUDE_DIR}
    ${EVENT_SYSTEM_INCLUDE_DIR}
    ${FILE_SERVICE_INCLUDE_DIR}
)

# for linking libs
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${UTILITY_PRO}
    ${EVENT_SYSTEM_PRO}
    ${FILE_SERVICE_PRO}
)

message(STATUS "Application tree reorganized!")

# folder structure in project
set_target_properties(
    ${UTILITY_PRO} ${EVENT_SYSTEM_PRO} ${FILE_SERVICE_PRO}
    PROPERTIES 
    FOLDER          "Core"
)
