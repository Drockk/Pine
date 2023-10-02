project (Pine)

add_library(
        Pine
        include/pine/Pine.hpp
        include/pine/MemberFunctionHandler.hpp
        include/pine/Event.hpp
        include/pine/EventBus.hpp
        include/pine/empty.cpp
)

if (CMAKE_VERSION VERSION_GREATER 3.26)
    set_property(TARGET Pine PROPERTY CXX_STANDARD 23)
endif()
