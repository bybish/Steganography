add_library(controller MainController.cpp)
target_link_libraries(controller Qt5::Widgets view model)