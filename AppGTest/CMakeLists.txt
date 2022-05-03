project("AppGTest")

file(GLOB HEADERS_SOURCES
    *.h
    *.hpp
    *.cc
    *.cpp
)

# lib HEADERs
include_directories(${PROJECT_NAME} PUBLIC
    ${gTEST_INCLUDE_DIR}
    ${UTILITY_INCLUDE_DIR}
    ${EVENT_SYSTEM_INCLUDE_DIR}
    ${FILE_SERVICE_INCLUDE_DIR}
)

# add to lib
add_executable(${PROJECT_NAME} ${HEADERS_SOURCES})

# lib HEADERs
target_include_directories(${PROJECT_NAME} PUBLIC
    ${gTEST_INCLUDE_DIR}
    ${UTILITY_INCLUDE_DIR}
    ${EVENT_SYSTEM_INCLUDE_DIR}
    ${FILE_SERVICE_INCLUDE_DIR}
)

# for linking libs
target_link_libraries(${PROJECT_NAME} PUBLIC
    gtest_main
    ${UTILITY_PRO}
    ${EVENT_SYSTEM_PRO}
    ${FILE_SERVICE_PRO}
)

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)

# folder structure in project
set_target_properties(
    gmock gmock_main gtest gtest_main
    PROPERTIES 
    FOLDER          "ThirdParty//GoogleTest"
)