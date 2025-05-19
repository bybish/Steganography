cmake_minimum_required(VERSION 3.14)

project(SteganographyApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Убедитесь, что Qt5 установлен в системе
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Добавляем поддиректории
add_subdirectory(model)
add_subdirectory(view)
add_subdirectory(controller)

# Главный исполняемый файл
add_executable(SteganographyApp main.cpp)

# Подключаем исходники
target_link_libraries(SteganographyApp
        Qt5::Widgets
        model
        view
        controller
)