cmake_minimum_required(VERSION 4.1.1)
project(Paz VERSION 0.0.2 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 23
		CMAKE_CXX_STANDARD_REQUIRED ON
)

set(QT_FORCE_CMP0156_TO_VALUE NEW) #Чтобы убрать warning о CMP0156


find_package( Qt6 6.10.0 REQUIRED COMPONENTS
							Core
							Widgets
)

qt_standard_project_setup()

qt_add_executable( Paz
                   src/main.cpp
									 src/backend/pomodoro-timer/timer-engine.hpp
									 src/backend/pomodoro-timer/timer-engine.cpp
									 src/backend/pomodoro-timer/pomodoro-phase.hpp
									 src/backend/pomodoro-timer/pomodoro-phase.cpp
									 src/backend/pomodoro-timer/pomodoro-manager.hpp
									 src/backend/pomodoro-timer/pomodoro-manager.cpp
                   src/core/enums.cpp
)

target_link_libraries( ${PROJECT_NAME} PRIVATE
											 Qt6::Core
											 Qt6::Widgets
)
