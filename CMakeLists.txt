cmake_minimum_required(VERSION 4.2)

project(Paz
		VERSION 0.2.0
		LANGUAGES CXX
)

find_package(Qt6 6.10 REQUIRED COMPONENTS
		Core
		Widgets
		#LinguistTools
)

qt_standard_project_setup()

add_subdirectory(src)