cmake_minimum_required(VERSION 4.2)

project(Paz
		VERSION 0.2.2
		LANGUAGES CXX
)

find_package(Qt6 6.10.1 REQUIRED COMPONENTS
		Core
		Widgets
		Quick
)

qt_standard_project_setup(
		REQUIRES 6.10.1,
		I18N_TRANSLATED_LANGUAGES ru
)

add_subdirectory(src)