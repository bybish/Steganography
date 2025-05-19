add_library(controller MainController.cpp)

target_link_libraries(controller
        PRIVATE
        Qt5::Widgets
        model
)