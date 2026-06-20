cmake_minimum_required(VERSION 3.16)

project(Paz
        VERSION 0.2.2
        LANGUAGES CXX
)

find_package(Qt6 REQUIRED COMPONENTS
        Core
        Widgets
        Quick
)

qt_standard_project_setup(REQUIRES 6.11)

qt_add_executable(PazApp
        main.cpp
        impl/pomodoro-timer.hpp impl/pomodoro-timer.cpp
        #impl/settings.hpp impl/settings.cpp
        #impl/main-window.hpp impl/main-window.cpp
        core/constants.hpp
        core/basic-types-aliases.hpp
)

qt_add_qml_module(PazApp
        URI Paz.PomodoroTimer
        VERSION 1.0
        SOURCES
            impl/pomodoro-timer.hpp impl/pomodoro-timer.cpp
        QML_FILES
            ui/qml/Main.qml
            #ui/qml/PomodoroTimerWidget.qml
)

target_link_libraries(PazApp PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Quick
)

target_include_directories(PazApp PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/impl
)

target_compile_features(PazApp PUBLIC cxx_std_23)