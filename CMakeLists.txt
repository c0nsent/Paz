cmake_minimum_required(VERSION 4.2)

project(Test
		LANGUAGES CXX
)

find_package(Qt6 6.10 REQUIRED COMPONENTS
		Core
)

set(QT_FORCE_CMP0156_TO_VALUE NEW)

qt_standard_project_setup()

qt_add_executable(Test test.cpp)

target_link_libraries(Test PRIVATE Qt6::Core)

project(Paz
		VERSION 0.0.3
		LANGUAGES CXX
)

find_package(Qt6 6.10 REQUIRED COMPONENTS
		Core
		Widgets
)

qt_standard_project_setup()

add_subdirectory(src)