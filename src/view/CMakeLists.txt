set(CMAKE_INCLUDE_CURRENT_DIR ON)

qt5_wrap_ui(UIS_HDRS MainWindow.ui)

add_library(view MainWindow.cpp ${UIS_HDRS})
target_link_libraries(view Qt5::Widgets)