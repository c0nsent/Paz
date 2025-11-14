cmake_minimum_required(VERSION 4.1.1)
project(Paz VERSION 0.0.1 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 23
		CMAKE_CXX_STANDARD_REQUIRED ON
)

set(QT_FORCE_CMP0156_TO_VALUE NEW) #Чтобы убрать warning о CMP0156


find_package( Qt6 6.9.2 REQUIRED COMPONENTS
							Core
							Widgets
              Sql
)

qt_standard_project_setup()

qt_add_executable( Paz
									 src/main.cxx
									 src/backend/pomodoro-timer-backend.hpp
                   src/backend/pomodoro-timer-backend.cpp
)

target_link_libraries( ${PROJECT_NAME} PRIVATE
											 Qt6::Core
											 Qt6::Widgets
                       Qt6::Sql
)
