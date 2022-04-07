project("AppGTest")

file(GLOB HEADERS_SOURCES
    *.h
    *.hpp
    *.cc
    *.cpp
)


# add to lib
add_executable(${PROJECT_NAME} ${HEADERS_SOURCES})

# lib HEADERs
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
