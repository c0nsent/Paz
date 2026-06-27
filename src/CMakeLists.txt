cmake_minimum_required(VERSION 3.16)

project(Paz
        VERSION 0.3.1
        LANGUAGES CXX
)

add_compile_definitions(APP_VERSION=\"${CMAKE_PROJECT_VERSION}\")

find_package(Qt6 REQUIRED COMPONENTS
        Core
        Gui
        Widgets
        Quick
)

qt_standard_project_setup(REQUIRES 6.11)

qt_add_executable(PazApp
        main.cpp
        impl/pomodoro-timer.hpp impl/pomodoro-timer.cpp
        impl/settings-manager.hpp impl/settings-manager.cpp
        impl/pomodoro-stats.hpp impl/pomodoro-stats.cpp
        core/constants.hpp
        core/basic-types-aliases.hpp
)

qt_add_qml_module(PazApp
        URI Paz
        VERSION 1.0
        SOURCES
            impl/pomodoro-timer.hpp impl/pomodoro-timer.cpp
            impl/settings-manager.hpp impl/settings-manager.cpp
            impl/pomodoro-stats.hpp impl/pomodoro-stats.cpp
        QML_FILES
            ui/qml/Main.qml
            ui/qml/TimerPage.qml
            ui/qml/SettingsPage.qml
            ui/qml/Sidebar.qml
)

target_link_libraries(PazApp PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Quick
)

target_include_directories(PazApp PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/impl
)

target_compile_features(PazApp PUBLIC cxx_std_23)