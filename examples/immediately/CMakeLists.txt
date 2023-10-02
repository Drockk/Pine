project (Immediately)

add_executable(
        Immediately
        main.cpp
)

message(
        ${PINE_INCLUDE_PATH}
)
target_include_directories(Immediately PRIVATE
        ${PINE_INCLUDE_PATH}/
)
target_link_libraries(Immediately PRIVATE Pine)

if (CMAKE_VERSION VERSION_GREATER 3.26)
        set_property(TARGET Immediately PROPERTY CXX_STANDARD 23)
endif()
