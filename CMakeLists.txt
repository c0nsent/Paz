cmake_minimum_required(VERSION 4.2)

project(Paz
		VERSION 0.2.0
		LANGUAGES CXX
)

find_package(Qt6 6.10 REQUIRED COMPONENTS
		Core
		Widgets
		LinguistTools
)

qt_standard_project_setup(I18N_TRANSLATED_LANGUAGES ru)

#qt_add_translations(Paz)

set(STYLE_SOURCE "${CMAKE_SOURCE_DIR}/themes/default/style.qss")
set(STYLE_DEST   "${CMAKE_BINARY_DIR}/themes/default/style.qss")

add_custom_command(
		OUTPUT ${STYLE_DEST}
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${STYLE_SOURCE} ${STYLE_DEST}
		DEPENDS ${STYLE_SOURCE}
		COMMENT "Copying qss file"
)

add_custom_target(CopyStyleFile ALL
	DEPENDS ${STYLE_DEST}
)

add_subdirectory(src)