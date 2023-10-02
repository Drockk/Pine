project (Deferred)

add_executable(
        Deferred
        main.cpp
)

message(
        ${PINE_INCLUDE_PATH}
)
target_include_directories(Deferred PRIVATE
        ${PINE_INCLUDE_PATH}/
)
target_link_libraries(Deferred PRIVATE Pine)

if (CMAKE_VERSION VERSION_GREATER 3.26)
        set_property(TARGET Deferred PROPERTY CXX_STANDARD 23)
endif()
