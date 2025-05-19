add_subdirectory(model)
add_subdirectory(view)
add_subdirectory(controller)

add_executable(SteganographyGUI main.cpp main.h)

target_link_libraries(SteganographyGUI
        Qt5::Widgets
        model
        view
        controller
)