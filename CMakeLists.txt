cmake_minimum_required(VERSION 3.21)

project(MultifunctionalCurrencyConverter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

qt_add_executable(currency_converter
    src/main.cpp
    src/MainWindow.cpp
    src/MainWindow.h
)

target_link_libraries(currency_converter
    PRIVATE
        Qt6::Widgets
        Qt6::Network
)

if(WIN32)
    set_target_properties(currency_converter PROPERTIES WIN32_EXECUTABLE ON)
endif()
