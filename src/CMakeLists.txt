cmake_minimum_required(VERSION 4.2)

project(Paz
        VERSION 0.2.2
        LANGUAGES CXX
)

find_package(Qt6 6.11.1 REQUIRED COMPONENTS
        Core
        Quick
        Qml
)

qt_standard_project_setup()

qt_add_executable(Paz
        main.cpp
        impl/pomodoro-timer.hpp impl/pomodoro-timer.cpp
        core/constants.hpp
        core/basic-types-aliases.hpp
)

qt_add_qml_module(Paz
        URI PazQml
        VERSION 1.0
        SOURCES
        impl/pomodoro-timer.hpp impl/pomodoro-timer.cpp
        QML_FILES
        ui/qml/Main.qml

)

target_link_libraries(Paz PRIVATE
        Qt6::Core
        Qt6::Quick
        Qt6::Qml
)

target_compile_features(Paz PUBLIC cxx_std_23)