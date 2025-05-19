set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_library(view MainWindow.cpp MainWindow.ui)
target_link_libraries(view Qt5::Widgets)
target_include_directories(view PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})